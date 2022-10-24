#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    this->_clock = clock;
    this->_window = window;
    this->_sprites = sprites;
    if (!this->_font.loadFromFile("R-Type/Assets/Fonts/PeachDays.ttf"))
        throw std::runtime_error("Error: Font not found");
    this->_text.setFont(this->_font);
    this->_text.setCharacterSize(20);
    this->_text.setFillColor(sf::Color::White);
}

void RenderSystem::displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();

    std::size_t cooldownBarParent = (InfoComp::COOLDOWNBAR | InfoComp::SPRITEID | InfoComp::PARENT);
    std::size_t cooldownBarChild = (InfoComp::COOLDOWNSHOOT);

    if (masks[i].has_value() && (masks[i].value() & cooldownBarParent) == cooldownBarParent) {
        std::size_t idPar = componentManager.getSingleComponent<Parent>(i).id;
        if (masks[idPar].has_value()) {
            if ((masks[idPar].value() & cooldownBarChild) == cooldownBarChild) {
                CooldownShoot &cooldownShoot = componentManager.getSingleComponent<CooldownShoot>(idPar);
                spriteRef.setScale(((this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * 100 / cooldownShoot.shootDelay) > 100
                                       ? 100
                                       : (this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * 100 / cooldownShoot.shootDelay,
                                   1);
            }
        } else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
        }
    }
}

void RenderSystem::displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();
    std::size_t lifeBarParent = (InfoComp::POS | InfoComp::LIFEBAR | InfoComp::PARENT);
    std::size_t lifeBarChild = (InfoComp::POS | InfoComp::LIFE | InfoComp::SIZE);

    if (masks[i].has_value() && (masks[i].value() & lifeBarParent) == lifeBarParent) {
        std::size_t idPar = componentManager.getSingleComponent<Parent>(i).id;
        if (masks[idPar].has_value()) {
            if ((masks[idPar].value() & lifeBarChild) == lifeBarChild) {
                LifeBar &lifeBar = componentManager.getSingleComponent<LifeBar>(i);
                Life &life = componentManager.getSingleComponent<Life>(idPar);
                Position &pos = componentManager.getSingleComponent<Position>(idPar);
                Size &sz = componentManager.getSingleComponent<Size>(idPar);
                spriteRef.setScale(life.life * sz.x / lifeBar.lifeMax, 1);
                spriteRef.setPosition(pos.x, pos.y - 20);
            }
        } else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
        }
    }
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t render = (InfoComp::POS | InfoComp::SPRITEID);
    std::size_t renderAnim = (InfoComp::SPRITEAT);
    std::size_t renderCooldown = (InfoComp::PARENT | InfoComp::COOLDOWNBAR);
    std::size_t renderLife = (InfoComp::PARENT | InfoComp::LIFEBAR);
    std::size_t renderParallax = (InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARALLAX);
    std::size_t renderText = (InfoComp::TEXT);
    std::size_t renderButton = (InfoComp::POS | InfoComp::SPRITEID | InfoComp::BUTTON);
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;
    std::vector<sf::Text> stockText;
    std::vector<sf::Sprite> stockButton;

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & renderText) == renderText) {
            this->_text.setString(componentManager.getSingleComponent<Text>(i).str + std::to_string(componentManager.getSingleComponent<Text>(i).value));
            this->_text.setPosition(componentManager.getSingleComponent<Text>(i).pos);
            stockText.push_back(this->_text);
            continue;
        }
        if (masks[i].has_value() && (masks[i].value() & renderButton) == renderButton) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            SpriteID &spriteId = componentManager.getSingleComponent<SpriteID>(i);
            sf::Sprite &spriteRef = this->_sprites->at(spriteId.id);
            spriteRef.setPosition(pos.x, pos.y);
            stockButton.push_back(spriteRef);
            continue;
        }
        if (masks[i].has_value() && (masks[i].value() & render) == render) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            SpriteID &spriteId = componentManager.getSingleComponent<SpriteID>(i);
            sf::Sprite &spriteRef = this->_sprites->at(spriteId.id);
            spriteRef.setPosition(pos.x, pos.y);
            if (masks[i].has_value() && (masks[i].value() & renderAnim) == renderAnim) {
                spriteRef.setTextureRect(static_cast<sf::IntRect>(componentManager.getSingleComponent<SpriteAttribut>(i).rect));
                spriteRef.setRotation(componentManager.getSingleComponent<SpriteAttribut>(i).rotation);
                spriteRef.setColor(componentManager.getSingleComponent<SpriteAttribut>(i).color);
                spriteRef.setScale(componentManager.getSingleComponent<SpriteAttribut>(i).scale);
            }
            if (masks[i].has_value() && (masks[i].value() & renderCooldown) == renderCooldown)
                displayCooldownBar(componentManager, entityManager, spriteRef, i);
            if (masks[i].has_value() && (masks[i].value() & renderLife) == renderLife)
                displayLifeBar(componentManager, entityManager, spriteRef, i);
            if (spriteId.priority == Priority::HIGH)
                stockSpriteHigh.push_back(spriteRef);
            if (spriteId.priority == Priority::MEDIUM)
                stockSpriteMedium.push_back(spriteRef);
            if (spriteId.priority == Priority::LOW)
                stockSpriteLow.push_back(spriteRef);
        }
    }
    for (std::size_t i = 0; i < stockSpriteHigh.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & renderParallax) == renderParallax) {
            stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x + _window->getSize().x, stockSpriteHigh[i].getPosition().y);
            this->_window->draw(stockSpriteHigh[i]);
            stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x - _window->getSize().x, stockSpriteHigh[i].getPosition().y);
        }
        this->_window->draw(stockSpriteHigh[i]);
    }
    for (std::size_t i = 0; i < stockSpriteMedium.size(); i++)
        this->_window->draw(stockSpriteMedium[i]);
    for (std::size_t i = 0; i < stockText.size(); i++)
        this->_window->draw(stockText[i]);
    for (std::size_t i = 0; i < stockSpriteLow.size(); i++)
        this->_window->draw(stockSpriteLow[i]);


}

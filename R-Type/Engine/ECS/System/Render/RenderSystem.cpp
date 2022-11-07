#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
    this->_sprites = sprites;
    if (!this->_font.loadFromFile("R-Type/Assets/Fonts/PeachDays.ttf"))
        throw std::runtime_error("Error: Font not found");
    this->_text.setFont(this->_font);
    this->_text.setCharacterSize(20);
    this->_text.setFillColor(sf::Color::White);

    entityManager.addMaskCategory(InfoComp::TEXT);
    entityManager.addMaskCategory(InfoComp::POS | InfoComp::SPRITEID);
}

void RenderSystem::displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();

    std::size_t cooldownBarParent = (InfoComp::COOLDOWNBAR | InfoComp::SPRITEID | InfoComp::PARENT);
    std::size_t cooldownBarChild = (InfoComp::COOLDOWNSHOOT);
    std::size_t size = 100 / this->_screenSize->x * this->_window->getSize().x;

    if (masks[i].has_value() && (masks[i].value() & cooldownBarParent) == cooldownBarParent) {
        std::size_t idPar = componentManager.getSingleComponent<Parent>(i).id;
        if (masks[idPar].has_value()) {
            if ((masks[idPar].value() & cooldownBarChild) == cooldownBarChild) {
                CooldownShoot &cooldownShoot = componentManager.getSingleComponent<CooldownShoot>(idPar);
                spriteRef.setScale(((this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * size / cooldownShoot.shootDelay) > size
                                       ? size
                                       : (this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * size / cooldownShoot.shootDelay,
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
                spriteRef.setPosition(pos.x, pos.y - (20 / this->_screenSize->x * this->_window->getSize().x));
            }
        } else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
        }
    }
}

void RenderSystem::displayShield(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();
    std::size_t shieldParent = (InfoComp::POS | InfoComp::SHIELD | InfoComp::PARENT);
    std::size_t shieldChild = (InfoComp::POS | InfoComp::LIFE | InfoComp::SIZE);

    if (masks[i].has_value() && (masks[i].value() & shieldParent) == shieldParent) {
        std::size_t idPar = componentManager.getSingleComponent<Parent>(i).id;
        if (masks[idPar].has_value()) {
            if ((masks[idPar].value() & shieldChild) == shieldChild) {
                Shield &shield = componentManager.getSingleComponent<Shield>(i);
                if (shield.life > 0) {
                    Position &pos = componentManager.getSingleComponent<Position>(idPar);
                    Size &size = componentManager.getSingleComponent<Size>(idPar);
                    // spriteRef.setScale(shield.life * size.x / shield.defaultLife, shield.life * size.y / shield.defaultLife);
                    spriteRef.setPosition(pos.x, pos.y);
                    spriteRef.setScale(0.3, 0.3);
                    spriteRef.setRotation(componentManager.getSingleComponent<SpriteAttribut>(idPar).rotation);
                } else {
                    componentManager.removeAllComponents(i);
                    entityManager.removeMask(i);
                }
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
    std::size_t renderShield = (InfoComp::PARENT | InfoComp::SHIELD);
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;
    std::vector<sf::Text> stockText;
    std::vector<sf::Sprite> stockButton;

    for (auto id : entityManager.getMaskCategory(renderText)) {
        this->_text.setCharacterSize(20 / this->_screenSize->x * this->_window->getSize().x);
        if (componentManager.getSingleComponent<Text>(id).hasValue)
            this->_text.setString(componentManager.getSingleComponent<Text>(id).str + std::to_string(componentManager.getSingleComponent<Text>(id).value));
        else {
            this->_text.setString(componentManager.getSingleComponent<Text>(id).str);
            this->_text.setOrigin(this->_text.getLocalBounds().width / 2, this->_text.getLocalBounds().height / 2);
        }
        this->_text.setPosition(componentManager.getSingleComponent<Text>(id).pos);
        stockText.push_back(this->_text);
    }
    for (auto id : entityManager.getMaskCategory(render)) {
        Position &pos = componentManager.getSingleComponent<Position>(id);
        SpriteID &spriteId = componentManager.getSingleComponent<SpriteID>(id);

        sf::Sprite &spriteRef = this->_sprites->at(spriteId.id);
        spriteRef.setPosition(pos.x, pos.y);
        if (masks[id].has_value() && (masks[id].value() & renderAnim) == renderAnim) {
            SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(id);
            spriteRef.setTextureRect(static_cast<sf::IntRect>(spriteAt.rect));
            spriteRef.setRotation(spriteAt.rotation);
            spriteRef.setColor(spriteAt.color);
            spriteRef.setScale(spriteAt.scale);
            spriteRef.setOrigin(spriteAt.offset);
            spriteRef.setPosition(pos.x + spriteAt.offset.x * 1.5, pos.y + spriteAt.offset.y);
        }
        if (masks[id].has_value() && (masks[id].value() & renderCooldown) == renderCooldown)
            displayCooldownBar(componentManager, entityManager, spriteRef, id);
        if (masks[id].has_value() && (masks[id].value() & renderLife) == renderLife)
            displayLifeBar(componentManager, entityManager, spriteRef, id);
        if (masks[id].has_value() && (masks[id].value() & renderShield) == renderShield)
            displayShield(componentManager, entityManager, spriteRef, id);
        if (spriteId.priority == Priority::HIGH)
            stockSpriteHigh.push_back(spriteRef);
        if (spriteId.priority == Priority::MEDIUM)
            stockSpriteMedium.push_back(spriteRef);
        if (spriteId.priority == Priority::LOW)
            stockSpriteLow.push_back(spriteRef);
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
    for (std::size_t i = 0; i < stockSpriteLow.size(); i++)
        this->_window->draw(stockSpriteLow[i]);
    for (std::size_t i = 0; i < stockButton.size(); i++)
        this->_window->draw(stockButton[i]);
    for (std::size_t i = 0; i < stockText.size(); i++)
        this->_window->draw(stockText[i]);
}

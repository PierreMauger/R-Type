#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader)
{
    this->_clock = clock;
    this->_window = window;
    this->_sprites = loader.getSprites();
}

void RenderSystem::displaycooldownBar(ComponentManager &componentManager, sf::Sprite &spriteRef, std::size_t i)
{
    Component &spriteId = componentManager.getComponent(typeid(SpriteID));
    Component &cooldown = componentManager.getComponent(typeid(CooldownShoot));
    Component &parent = componentManager.getComponent(typeid(Parent));

    if (spriteId.getField(std::any_cast<Parent &>(parent.getField(i).value()).id).has_value()) {
        CooldownShoot &par = std::any_cast<CooldownShoot &>(cooldown.getField(std::any_cast<Parent &>(parent.getField(i).value()).id).value());
        spriteRef.setScale(((_clock->getElapsedTime().asSeconds() - par.lastShoot + par.shootDelay) * 100 / par.shootDelay) > 100
                               ? 100
                               : (_clock->getElapsedTime().asSeconds() - par.lastShoot + par.shootDelay) * 100 / par.shootDelay,
                           1);
    } else
        spriteRef.setScale(0, 0);
}

void RenderSystem::displayLifeBar(ComponentManager &componentManager, sf::Sprite &spriteRef, std::size_t i)
{
    Component &spriteId = componentManager.getComponent(typeid(SpriteID));
    Component &life = componentManager.getComponent(typeid(Life));
    Component &lifeBar = componentManager.getComponent(typeid(LifeBar));
    Component &parent = componentManager.getComponent(typeid(Parent));
    Component &size = componentManager.getComponent(typeid(Size));
    Component &position = componentManager.getComponent(typeid(Position));
    Component &app = componentManager.getComponent(typeid(Appearance));
    std::size_t idPar = std::any_cast<Parent &>(parent.getField(i).value()).id;

    if (spriteId.getField(idPar).has_value()) {
        if (app.getField(idPar).has_value() && std::any_cast<Appearance &>(app.getField(idPar).value()).app) {
            spriteRef.setScale(0, 0);
            return;
        }
        LifeBar &lb = std::any_cast<LifeBar &>(lifeBar.getField(i).value());
        Position &pos = std::any_cast<Position &>(position.getField(idPar).value());
        Life &par = std::any_cast<Life &>(life.getField(idPar).value());
        Size &sz = std::any_cast<Size &>(size.getField(idPar).value());
        spriteRef.setScale(sz.x * par.life / lb.lifeMax, 1);
        spriteRef.setPosition(pos.x, pos.y - 20);
    } else
        spriteRef.setScale(0, 0);
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t render = (InfoEntity::POS | InfoEntity::SPRITEID);
    std::size_t renderCooldown = (InfoEntity::PARENT | InfoEntity::COOLDOWNBAR);
    std::size_t renderLife = (InfoEntity::PARENT | InfoEntity::LIFEBAR);
    std::size_t renderParallax = (InfoEntity::POS | InfoEntity::SPRITEID | InfoEntity::PARALLAX);
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & render) == render) {
                Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                SpriteID &spriteId = std::any_cast<SpriteID &>(componentManager.getComponent(typeid(SpriteID)).getField(i).value());
                this->_sprites[spriteId.id].setPosition(pos.x, pos.y);
                this->_window->draw(this->_sprites[spriteId.id]);
                sf::Sprite &spriteRef = this->_sprites[std::any_cast<SpriteID &>(componentManager.getComponent(typeid(SpriteID)).getField(i).value()).id];
                if ((masks[i].value() & renderCooldown) == renderCooldown)
                    displaycooldownBar(componentManager, spriteRef, i);
                if ((masks[i].value() & renderLife) == renderLife)
                    displayLifeBar(componentManager, spriteRef, i);
                if (spriteId.priority == Priority::HIGH)
                    stockSpriteHigh.push_back(spriteRef);
                if (spriteId.priority == Priority::MEDIUM)
                    stockSpriteMedium.push_back(spriteRef);
                if (spriteId.priority == Priority::LOW)
                    stockSpriteLow.push_back(spriteRef);
            }
        }
    }
    for (std::size_t i = 0; i < stockSpriteHigh.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & renderParallax) == renderParallax) {
                stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x + _window->getSize().x, stockSpriteHigh[i].getPosition().y);
                this->_window->draw(stockSpriteHigh[i]);
                stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x - _window->getSize().x, stockSpriteHigh[i].getPosition().y);
            }
        }
        this->_window->draw(stockSpriteHigh[i]);
    }
    for (std::size_t i = 0; i < stockSpriteMedium.size(); i++)
        this->_window->draw(stockSpriteMedium[i]);
    for (std::size_t i = 0; i < stockSpriteLow.size(); i++)
        this->_window->draw(stockSpriteLow[i]);
}

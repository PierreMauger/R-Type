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
    Component &spriteId = componentManager.getComponent(typeid(SpriteID));
    Component &position = componentManager.getComponent(typeid(Position));
    Component &parent = componentManager.getComponent(typeid(Parent));
    Component &cooldownBar = componentManager.getComponent(typeid(CooldownBar));
    Component &lifeBar = componentManager.getComponent(typeid(LifeBar));
    Component &parallax = componentManager.getComponent(typeid(Parallax));
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;

    for (std::size_t i = 0; i < spriteId.getSize(); i++) {
        if (entityManager.getMasks()[i].has_value() && spriteId.getField(i).has_value()) {
            SpriteID &sprId = std::any_cast<SpriteID &>(spriteId.getField(i).value());
            sf::Sprite &spriteRef = this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id);
            if (position.getField(i).has_value()) {
                Position &pos = std::any_cast<Position &>(position.getField(i).value());
                this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id).setPosition(pos.x, pos.y);
            }
            if (cooldownBar.getField(i).has_value() && parent.getField(i).has_value())
                displaycooldownBar(componentManager, spriteRef, i);
            if (lifeBar.getField(i).has_value() && parent.getField(i).has_value())
                displayLifeBar(componentManager, spriteRef, i);
            if (sprId.priority == Priority::HIGH)
                stockSpriteHigh.push_back(spriteRef);
            if (sprId.priority == Priority::MEDIUM)
                stockSpriteMedium.push_back(spriteRef);
            if (sprId.priority == Priority::LOW)
                stockSpriteLow.push_back(spriteRef);
            for (std::size_t i = 0; i < stockSpriteHigh.size(); i++) {
                if (parallax.getField(i).has_value()) {
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
        }
    }
}

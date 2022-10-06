#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader)
{
    this->_clock = clock;
    this->_window = window;
    this->_sprites = loader.getSprites();
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &spriteId = componentManager.getComponent(typeid(SpriteID));
    Component &position = componentManager.getComponent(typeid(Position));
    Component &parent = componentManager.getComponent(typeid(Parent));
    Component &cooldown = componentManager.getComponent(typeid(CooldownShoot));
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
            if (parent.getField(i).has_value() && cooldown.getField(std::any_cast<Parent &>(parent.getField(i).value()).id).has_value()) {
                CooldownShoot &par = std::any_cast<CooldownShoot &>(cooldown.getField(std::any_cast<Parent &>(parent.getField(i).value()).id).value());
                spriteRef.setScale(((_clock->getElapsedTime().asSeconds() - par.time + par.cooldown) * 100 / par.cooldown) > 100
                                       ? 100
                                       : (_clock->getElapsedTime().asSeconds() - par.time + par.cooldown) * 100 / par.cooldown,
                                   1);
            }
            if (sprId.priority == Priority::HIGH) {
                stockSpriteHigh.push_back(spriteRef);
            } else if (sprId.priority == Priority::MEDIUM) {
                stockSpriteMedium.push_back(spriteRef);
            } else if (sprId.priority == Priority::LOW) {
                stockSpriteLow.push_back(spriteRef);
            }
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

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

    for (std::size_t i = 0; i < spriteId.getSize(); i++) {
        if (entityManager.getMasks()[i].has_value() && spriteId.getField(i).has_value()) {
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
            if (parallax.getField(i).has_value()) {
                spriteRef.setPosition(spriteRef.getPosition().x + _window->getSize().x, spriteRef.getPosition().y);
                this->_window->draw(spriteRef);
                spriteRef.setPosition(spriteRef.getPosition().x - _window->getSize().x, spriteRef.getPosition().y);
            }
            this->_window->draw(this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id));
        }
    }
}

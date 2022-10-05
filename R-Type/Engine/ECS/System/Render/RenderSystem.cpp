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

    for (std::size_t i = 0; i < spriteId.getSize(); i++) {
        if (entityManager.getMasks()[i].has_value() && spriteId.getField(i).has_value()) {
            if (position.getField(i).has_value()) {
                Position &pos = std::any_cast<Position &>(position.getField(i).value());
                this->_sprites->at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id).setPosition(pos.x, pos.y);
            }
            this->_window->draw(this->_sprites->at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id));
        }
    }
}

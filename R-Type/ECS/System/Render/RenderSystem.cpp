#include "ECS/System/Render/RenderSystem.hpp"

using namespace ECS;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
    if (!this->_texture.at(0).loadFromFile("/home/xavier/rtype/R-Type/assets/Sprites/space_background.jpg"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(1).loadFromFile("/home/xavier/rtype/R-Type/assets/Sprites/spaceship.png"))
        throw std::runtime_error("Background not found");
    this->_sprites.push_back(sf::Sprite(this->_texture[0]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.6, 0.63);
    this->_sprites.push_back(sf::Sprite(this->_texture[1]));
}

void RenderSystem::update(ComponentManager &componentManager)
{
    Component &modelId = componentManager.getComponent(typeid(ModelID));
    Component &position = componentManager.getComponent(typeid(Position));

    for (std::size_t i = 0; i < modelId.getSize(); i++) {
        if (modelId.getField(i).has_value()) {
            if (position.getField(i).has_value()) {
                Position &pos = std::any_cast<Position &>(position.getField(i).value());
                this->_sprites.at(std::any_cast<ModelID &>(modelId.getField(i).value()).id).setPosition(pos.x, pos.y);
            }
            this->_window->draw(this->_sprites.at(std::any_cast<ModelID &>(modelId.getField(i).value()).id));
        }
    }
}

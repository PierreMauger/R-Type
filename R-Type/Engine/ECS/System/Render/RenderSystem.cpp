#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock)
{
    this->_clock = clock;
    this->_window = window;
    if (!this->_texture.at(0).loadFromFile("./R-Type/Assets/Sprites/Background.jpg"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(1).loadFromFile("./R-Type/Assets/Sprites/Spaceship.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(2).loadFromFile("./R-Type/Assets/Sprites/Fireball.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(3).loadFromFile("./R-Type/Assets/Sprites/Parallax/Background.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(4).loadFromFile("./R-Type/Assets/Sprites/Parallax/Stars.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(5).loadFromFile("./R-Type/Assets/Sprites/Parallax/Moons.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(6).loadFromFile("./R-Type/Assets/Sprites/Parallax/Ring-Planet.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(7).loadFromFile("./R-Type/Assets/Sprites/Parallax/Planet.png"))
        throw std::runtime_error("Background not found");
    this->_sprites.push_back(sf::Sprite(this->_texture[0]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.6, 0.63);
    this->_sprites.push_back(sf::Sprite(this->_texture[1]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.5, 0.5);
    this->_sprites.push_back(sf::Sprite(this->_texture[2]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.3, 0.3);
    this->_sprites.push_back(sf::Sprite(this->_texture[3]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(3, 4);
    this->_sprites.push_back(sf::Sprite(this->_texture[4]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(3, 4);
    this->_sprites.push_back(sf::Sprite(this->_texture[5]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(3, 4);
    this->_sprites.push_back(sf::Sprite(this->_texture[6]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(3, 4);
    this->_sprites.push_back(sf::Sprite(this->_texture[7]));
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &spriteId = componentManager.getComponent(typeid(SpriteID));
    Component &position = componentManager.getComponent(typeid(Position));

    for (std::size_t i = 0; i < spriteId.getSize(); i++) {
        if (entityManager.getMasks()[i].has_value() && spriteId.getField(i).has_value()) {
            if (position.getField(i).has_value()) {
                Position &pos = std::any_cast<Position &>(position.getField(i).value());
                this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id).setPosition(pos.x, pos.y);
            }
            this->_window->draw(this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id));
        }
    }
}

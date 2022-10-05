#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock)
{
    this->_clock = clock;
    this->_window = window;
    if (!this->_texture.at(0).loadFromFile("./R-Type/assets/Sprites/space_background.jpg"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(1).loadFromFile("./R-Type/assets/Sprites/spaceship.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(2).loadFromFile("./R-Type/assets/Sprites/fireball.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(3).loadFromFile("./R-Type/assets/Sprites/background_parallax/parallax-space-backgound.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(4).loadFromFile("./R-Type/assets/Sprites/background_parallax/parallax-space-stars.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(5).loadFromFile("./R-Type/assets/Sprites/background_parallax/parallax-space-far-planets.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(6).loadFromFile("./R-Type/assets/Sprites/background_parallax/parallax-space-ring-planet.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(7).loadFromFile("./R-Type/assets/Sprites/background_parallax/parallax-space-big-planet.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(8).loadFromFile("./R-Type/assets/Sprites/cooldown_bar.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(9).loadFromFile("./R-Type/assets/Sprites/ennemi.png"))
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
    this->_sprites.push_back(sf::Sprite(this->_texture[8]));
    this->_sprites.push_back(sf::Sprite(this->_texture[9]));
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &spriteId = componentManager.getComponent(typeid(SpriteID));
    Component &position = componentManager.getComponent(typeid(Position));
    Component &parent = componentManager.getComponent(typeid(Parent));
    Component &cooldown = componentManager.getComponent(typeid(CooldownShoot));

    for (std::size_t i = 0; i < spriteId.getSize(); i++) {
        if (entityManager.getMasks()[i].has_value() && spriteId.getField(i).has_value()) {
            if (position.getField(i).has_value()) {
                Position &pos = std::any_cast<Position &>(position.getField(i).value());
                this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id).setPosition(pos.x, pos.y);
            }
            if (parent.getField(i).has_value() && cooldown.getField(std::any_cast<Parent &>(parent.getField(i).value()).id).has_value()) {
                CooldownShoot &par = std::any_cast<CooldownShoot &>(cooldown.getField(std::any_cast<Parent &>(parent.getField(i).value()).id).value());
                sf::Sprite &spriteRef = this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id);
                spriteRef.setScale(((_clock->getElapsedTime().asSeconds() - par.time + par.cooldown) * 100 / par.cooldown) > 100
                                       ? 100
                                       : (_clock->getElapsedTime().asSeconds() - par.time + par.cooldown) * 100 / par.cooldown,
                                   1);
            }
            this->_window->draw(this->_sprites.at(std::any_cast<SpriteID &>(spriteId.getField(i).value()).id));
        }
    }
}

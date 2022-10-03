#include "ECS/System/Render/RenderSystem.hpp"

using namespace ECS;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
    this->_cooldownBar = {};
    this->_color = {{0, sf::Color::Red}, {1, sf::Color::Blue}, {2, sf::Color::Green}, {3, sf::Color::Yellow}, {4, sf::Color::Magenta}};
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
            this->DisplayCooldownBar(i, componentManager);
            this->_window->draw(this->_sprites.at(std::any_cast<ModelID &>(modelId.getField(i).value()).id));
        }
    }
}

void RenderSystem::DisplayCooldownBar(std::size_t i, ComponentManager &componentManager)
{
    Component &cooldown = componentManager.getComponent(typeid(CooldownShoot));
    sf::Vector2f size(100, 10);
    sf::Vector2u pos(0, this->_window->getSize().y - 20);

    if (cooldown.getField(i).has_value()) {
        CooldownShoot &sht = std::any_cast<CooldownShoot &>(cooldown.getField(i).value());
        if (this->_cooldownBar.find(i) == this->_cooldownBar.end()) {
            pos.x = this->_cooldownBar.size() * (size.x + 10) + 10;
            this->_cooldownBar.insert({i, {sf::RectangleShape(sf::Vector2f(size.x, size.y)), sf::RectangleShape(sf::Vector2f(0, size.y))}});
            this->_cooldownBar.at(i).first.setOutlineColor(sf::Color::Black);
            this->_cooldownBar.at(i).first.setOutlineThickness(2);
            this->_cooldownBar.at(i).first.setPosition(pos.x, pos.y);
            this->_cooldownBar.at(i).second.setFillColor(this->_color.at(this->_cooldownBar.size() - 1));
            this->_cooldownBar.at(i).second.setPosition(pos.x, pos.y);
        }
        this->_cooldownBar.at(i).second.setSize(
            {(sht.clock.getElapsedTime().asSeconds() * size.x / sht.time.asSeconds()) > size.x ? size.x : sht.clock.getElapsedTime().asSeconds() * size.x / sht.time.asSeconds(),
             size.y});
        this->_window->draw(this->_cooldownBar.at(i).first);
        this->_window->draw(this->_cooldownBar.at(i).second);
    }
}
#include "ECS/System/Render/RenderSystem.hpp"

using namespace ECS;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
    this->_couldownBar = {};
    this->_color = {{0, sf::Color::Red}, {1, sf::Color::Blue}, {2, sf::Color::Green}, {3, sf::Color::Yellow}, {4, sf::Color::Magenta}};
    if (!this->_texture.at(0).loadFromFile("./R-Type/assets/Sprites/space_background.jpg"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(1).loadFromFile("./R-Type/assets/Sprites/spaceship.png"))
        throw std::runtime_error("Background not found");
    if (!this->_texture.at(2).loadFromFile("./R-Type/assets/Sprites/fireball.png"))
        throw std::runtime_error("Background not found");
    this->_sprites.push_back(sf::Sprite(this->_texture[0]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.6, 0.63);
    this->_sprites.push_back(sf::Sprite(this->_texture[1]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.5, 0.5);
    this->_sprites.push_back(sf::Sprite(this->_texture[2]));
    this->_sprites.at(this->_sprites.size() - 1).setScale(0.3, 0.3);
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
            this->DisplayCouldownBar(i, componentManager);
            this->_window->draw(this->_sprites.at(std::any_cast<ModelID &>(modelId.getField(i).value()).id));
        }
    }
}

void RenderSystem::DisplayCouldownBar(std::size_t i, ComponentManager &componentManager)
{
    Component &couldown = componentManager.getComponent(typeid(CouldownShoot));
    sf::Vector2f size(100, 10);
    sf::Vector2u pos(0, this->_window->getSize().y - 20);

    if (couldown.getField(i).has_value()) {
        CouldownShoot &sht = std::any_cast<CouldownShoot &>(couldown.getField(i).value());
        if (this->_couldownBar.find(i) == this->_couldownBar.end()) {
            pos.x = this->_couldownBar.size() * (size.x + 10) + 10;
            this->_couldownBar.insert({i, {sf::RectangleShape(sf::Vector2f(size.x, size.y)), sf::RectangleShape(sf::Vector2f(0, size.y))}});
            this->_couldownBar.at(i).first.setOutlineColor(sf::Color::Black);
            this->_couldownBar.at(i).first.setOutlineThickness(2);
            this->_couldownBar.at(i).first.setPosition(pos.x, pos.y);
            this->_couldownBar.at(i).second.setFillColor(this->_color.at(this->_couldownBar.size() - 1));
            this->_couldownBar.at(i).second.setPosition(pos.x, pos.y);
        }
        this->_couldownBar.at(i).second.setSize(
            {(sht.clock.getElapsedTime().asSeconds() * size.x / sht.time.asSeconds()) > size.x ? size.x : sht.clock.getElapsedTime().asSeconds() * size.x / sht.time.asSeconds(),
             size.y});
        this->_window->draw(this->_couldownBar.at(i).first);
        this->_window->draw(this->_couldownBar.at(i).second);
    }
}
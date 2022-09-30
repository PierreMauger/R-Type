#include "ECS/System/Input/InputSystem.hpp"

using namespace ECS;

InputSystem::InputSystem(sf::Event &event)
{
    this->_event = std::make_shared<sf::Event>(event);
}

void InputSystem::update(ComponentManager &componentManager)
{
    Component &controllable = componentManager.getComponent(typeid(Controllable));
    Component &velocity = componentManager.getComponent(typeid(Velocity));

    for (std::size_t i = 0; i < controllable.getSize(); i++) {
        if (controllable.getField(i).has_value()) {
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = -2 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = 2 : vel.x = 0);
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = -2 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = 2 : vel.y = 0);
        }
    }
}
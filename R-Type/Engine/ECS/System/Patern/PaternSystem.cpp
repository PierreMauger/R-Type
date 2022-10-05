#include "Engine/ECS/System/Patern/PaternSystem.hpp"

using namespace eng;

PaternSystem::PaternSystem(std::shared_ptr<sf::Clock> clock)
{
    this->_clock = clock;
}

void PaternSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &position = componentManager.getComponent(typeid(Position));
    Component &velocity = componentManager.getComponent(typeid(Velocity));
    Component &patern = componentManager.getComponent(typeid(Patern));

    for (std::size_t i = 0; i < position.getSize(); i++) {
        if (position.getField(i).has_value() && velocity.getField(i).has_value() && patern.getField(i).has_value()) {
            Position &pos = std::any_cast<Position &>(position.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            Patern &pat = std::any_cast<Patern &>(patern.getField(i).value());
            pos.x += vel.x;
            if (pat.type == TypePatern::OSCILLATION) {
                pos.y = pat.center + std::sin(pat.angle) * RADIUS;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC;
            }
            if (pat.type == TypePatern::BIGOSCILLATION) {
                pos.y = pat.center + std::sin(pat.angle) * (RADIUS * 3);
                pat.angle = this->_clock->getElapsedTime().asSeconds() * (SPEED_OSC / 2);
            }
        }
    }
}
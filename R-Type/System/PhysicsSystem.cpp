#include "PhysicsSystem.hpp"

using namespace ECS;

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::update(ComponentManager componentManager)
{
    std::vector<std::optional<std::any>> &position = componentManager.getComponent(typeid(Position));
    std::vector<std::optional<std::any>> &velocity = componentManager.getComponent(typeid(Velocity));

    for (std::size_t i = 0; i < position.size(); i++) {
        if (position[i].has_value() && velocity[i].has_value()) {
            Position &pos = std::any_cast<Position &>(position[i].value());
            Velocity &vel = std::any_cast<Velocity &>(velocity[i].value());
            pos.x += vel.x;
            pos.y += vel.y;
        }
    }
}
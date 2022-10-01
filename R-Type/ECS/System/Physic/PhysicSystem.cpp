#include "ECS/System/Physic/PhysicSystem.hpp"

using namespace ECS;

PhysicSystem::PhysicSystem()
{
}

void PhysicSystem::update(ComponentManager &componentManager)
{
    Component &position = componentManager.getComponent(typeid(Position));
    Component &velocity = componentManager.getComponent(typeid(Velocity));

    for (std::size_t i = 0; i < position.getSize(); i++) {
        if (position.getField(i).has_value() && velocity.getField(i).has_value()) {
            Position &pos = std::any_cast<Position &>(position.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.x > 5000 || pos.y > 5000)
                componentManager.killEntity(i);
            if (pos.x < -800)
                pos.x = 800;
        }
    }
}

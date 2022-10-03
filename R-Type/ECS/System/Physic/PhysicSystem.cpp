#include "ECS/System/Physic/PhysicSystem.hpp"

using namespace ECS;

PhysicSystem::PhysicSystem()
{
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &position = componentManager.getComponent(typeid(Position));
    Component &velocity = componentManager.getComponent(typeid(Velocity));

    for (std::size_t i = 0; i < position.getSize(); i++) {
        if (position.getField(i).has_value() && velocity.getField(i).has_value()) {
            Position &pos = std::any_cast<Position &>(position.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.x > 1000 || pos.y > 1000) {
                componentManager.killEntity(i);
                entityManager.removeMask(i);
            }
            if (pos.x < -800)
                pos.x = 800;
        }
    }
}

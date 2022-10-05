#include "Engine/ECS/System/Patern/PaternSystem.hpp"

using namespace eng;

PaternSystem::PaternSystem()
{
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
            if (pat.type == TypePatern::LINE)
                pos.x += vel.x;
        }
    }
}
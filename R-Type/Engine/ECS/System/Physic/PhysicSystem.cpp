#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
}

bool PhysicSystem::collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    Component &con = componentManager.getComponent(typeid(Controllable));
    Component &enemy = componentManager.getComponent(typeid(Enemy));
    Component &position = componentManager.getComponent(typeid(Position));

    if (con.getField(i).has_value()) {
        pos.x < 0 ? pos.x = 0 : pos.x;
        pos.y < 0 ? pos.y = 0 : pos.y;
        pos.x > _window->getSize().x - 100 ? pos.x = _window->getSize().x - 100 : pos.x;
        pos.y > _window->getSize().y - 100 ? pos.y = _window->getSize().y - 100 : pos.y;
        for (std::size_t j = 0; j < position.getSize(); j++) {
            if (position.getField(j).has_value() && enemy.getField(j).has_value()) {
                Position &pos2 = std::any_cast<Position &>(position.getField(j).value());
                if (pos.x > pos2.x - 90 && pos.x < pos2.x + 90 && pos.y > pos2.y - 90 && pos.y < pos2.y + 90) {
                    componentManager.killEntity(i);
                    entityManager.removeMask(i);
                    return true;
                }
            }
        }
        return true;
    }
    return false;
}

bool PhysicSystem::collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    Component &proj = componentManager.getComponent(typeid(Projectile));
    Component &enemy = componentManager.getComponent(typeid(Enemy));
    Component &position = componentManager.getComponent(typeid(Position));

    if (proj.getField(i).has_value()) {
        for (std::size_t j = 0; j < position.getSize(); j++) {
            if (position.getField(j).has_value() && enemy.getField(j).has_value()) {
                Position &pos2 = std::any_cast<Position &>(position.getField(j).value());
                if (pos.x > pos2.x - 10 && pos.x < pos2.x + 10 && pos.y > pos2.y - 20 && pos.y < pos2.y + 110) {
                    componentManager.killEntity(j);
                    entityManager.removeMask(j);
                    componentManager.killEntity(i);
                    entityManager.removeMask(i);
                    return true;
                }
            }
        }
    }
    return false;
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &position = componentManager.getComponent(typeid(Position));
    Component &velocity = componentManager.getComponent(typeid(Velocity));
    Component &parallax = componentManager.getComponent(typeid(Parallax));
    Component &pat = componentManager.getComponent(typeid(Patern));

    for (std::size_t i = 0; i < position.getSize(); i++) {
        if (position.getField(i).has_value() && velocity.getField(i).has_value() && !pat.getField(i).has_value()) {
            Position &pos = std::any_cast<Position &>(position.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            pos.x += vel.x;
            pos.y += vel.y;
            if (collisionFireball(i, componentManager, entityManager, pos))
                continue;
            if (collisionEnemy(i, componentManager, entityManager, pos))
                continue;
            if (parallax.getField(i).has_value())
                pos.x <= -800 ? pos.x = 800 : pos.x;
            else if (pos.x > _window->getSize().x || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
                componentManager.killEntity(i);
                entityManager.removeMask(i);
            }
        }
    }
}

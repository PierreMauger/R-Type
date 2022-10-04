#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &position = componentManager.getComponent(typeid(Position));
    Component &velocity = componentManager.getComponent(typeid(Velocity));
    Component &con = componentManager.getComponent(typeid(Controllable));
    Component &par = componentManager.getComponent(typeid(Parallax));

    for (std::size_t i = 0; i < position.getSize(); i++) {
        if (position.getField(i).has_value() && velocity.getField(i).has_value()) {
            Position &pos = std::any_cast<Position &>(position.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            pos.x += vel.x;
            pos.y += vel.y;
            if (con.getField(i).has_value()) {
                pos.x < 0 ? pos.x = 0 : pos.x; 
                pos.y < 0 ? pos.y = 0 : pos.y;
                pos.x > _window->getSize().x - 100 ? pos.x = _window->getSize().x - 100 : pos.x;
                pos.y > _window->getSize().y - 100 ? pos.y = _window->getSize().y - 100 : pos.y;
                continue;
            }
            if (par.getField(i).has_value())
                pos.x == -800 ? pos.x = 800 : pos.x;
            else if (pos.x > _window->getSize().x || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
                componentManager.killEntity(i);
                entityManager.removeMask(i);
            }
        }
    }
}

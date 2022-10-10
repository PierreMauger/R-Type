#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicSpeed = (InfoEntity::VEL | InfoEntity::POS);
    std::size_t physicControl = (InfoEntity::CONTROLLABLE | InfoEntity::POS);
    std::size_t physicPar = (InfoEntity::VEL | InfoEntity::POS | InfoEntity::PARALLAX);

    std::vector<std::size_t> tempDelete;

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & physicSpeed) == physicSpeed) {
                Velocity &vel = std::any_cast<Velocity &>(componentManager.getComponent(typeid(Velocity)).getField(i).value());
                Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                pos.x += vel.x;
                pos.y += vel.y;
                if ((masks[i].value() & physicControl) == physicControl) {
                    Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                    pos.x < 0 ? pos.x = 0 : pos.x;
                    pos.y < 0 ? pos.y = 0 : pos.y;
                    pos.x > _window->getSize().x - 100 ? pos.x = _window->getSize().x - 100 : pos.x;
                    pos.y > _window->getSize().y - 100 ? pos.y = _window->getSize().y - 100 : pos.y;
                    continue;
                }
                if ((masks[i].value() & physicPar) != physicPar) {
                    if (pos.x > _window->getSize().x || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
                        entityManager.removeMask(i);
                        componentManager.removeAllComponents(i);
                    }
                } else {
                    pos.x <= -800 ? pos.x = 800 : pos.x;
                }
            }
        }
    }
}

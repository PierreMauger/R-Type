#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
}

bool PhysicSystem::collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicCon = (InfoEntity::CONTROLLABLE);
    std::size_t physicCol = (InfoEntity::POS | InfoEntity::ENEMY | InfoEntity::SIZE);

    if ((masks[i].value() & physicCon) == physicCon) {
        pos.x < 0 ? pos.x = 0 : pos.x;
        pos.y < 0 ? pos.y = 0 : pos.y;
        pos.x > _window->getSize().x - 100 ? pos.x = _window->getSize().x - 100 : pos.x;
        pos.y > _window->getSize().y - 100 ? pos.y = _window->getSize().y - 100 : pos.y;
        for (std::size_t j = 0; j < masks.size(); j++) {
            if ((masks[i].value() & physicCol) == physicCol) {
                Position &pos2 = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                Size &sz = std::any_cast<Size &>(componentManager.getComponent(typeid(Size)).getField(i).value());
                if (pos.x >= pos2.x && pos.x <= pos2.x + sz.x && pos.y >= pos2.y && pos.y <= pos2.y + sz.y) {
                    componentManager.removeAllComponents(i);
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
    auto &masks = entityManager.getMasks();
    std::size_t physicProj = (InfoEntity::PROJECTILE | InfoEntity::PARENT | InfoEntity::POS);
    std::size_t physicApp = (InfoEntity::APP);
    std::size_t physicCon = (InfoEntity::CONTROLLABLE);
    std::size_t physicEne = (InfoEntity::ENEMY);

    if (masks[i].has_value()) {
        if ((masks[i].value() & physicProj) == physicProj) {
            Parent &par = std::any_cast<Parent &>(componentManager.getComponent(typeid(Parent)).getField(i).value());
            for (std::size_t j = 0; j < masks.size(); j++) {
                if (masks[j].has_value()) {
                    if (((masks[j].value() & physicCon) == physicCon || (masks[j].value() & physicEne) == physicEne) && par.id != j) {
                        if ((masks[j].value() & physicApp) == physicApp && std::any_cast<Appearance &>(componentManager.getComponent(typeid(Appearance)).getField(j).value()).app)
                            continue;
                        Position &pos2 = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(j).value());
                        Size &sz = std::any_cast<Size &>(componentManager.getComponent(typeid(Size)).getField(j).value());
                        if (pos.x >= pos2.x && pos.x <= pos2.x + sz.x && pos.y >= pos2.y && pos.y <= pos2.y + sz.y) {
                            Life &hp = std::any_cast<Life &>(componentManager.getComponent(typeid(Life)).getField(j).value());
                            hp.life -= 1;
                            if (hp.life == 0) {
                                componentManager.removeAllComponents(j);
                                entityManager.removeMask(j);
                            }
                            componentManager.removeAllComponents(i);
                            entityManager.removeMask(i);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicSpeed = (InfoEntity::VEL | InfoEntity::POS);
    std::size_t physicControl = (InfoEntity::CONTROLLABLE | InfoEntity::POS);
    std::size_t physicPar = (InfoEntity::VEL | InfoEntity::POS | InfoEntity::PARALLAX);
    std::size_t physicPat = (InfoEntity::PATERN);
    std::size_t physicAppear = (InfoEntity::APP);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & physicSpeed) == physicSpeed) {
                Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                Velocity &vel = std::any_cast<Velocity &>(componentManager.getComponent(typeid(Velocity)).getField(i).value());
                if ((masks[i].value() & physicAppear) == physicAppear) {
                    Appearance &app = std::any_cast<Appearance &>(componentManager.getComponent(typeid(Appearance)).getField(i).value());
                    if (app.app) {
                        pos.y -= vel.y;
                        if (pos.y >= app.end) {
                            vel.y = 0;
                            app.app = false;
                        }
                        continue;
                    }
                }
                if ((masks[i].value() & physicPat) != physicPat) {
                    pos.x += vel.x;
                    pos.y += vel.y;
                    if (collisionFireball(i, componentManager, entityManager, pos))
                        continue;
                    if (collisionEnemy(i, componentManager, entityManager, pos))
                        continue;
                    if ((masks[i].value() & physicControl) == physicControl) {
                        Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                        pos.x < 0 ? pos.x = 0 : pos.x;
                        pos.y < 0 ? pos.y = 0 : pos.y;
                        pos.x > _window->getSize().x - 100 ? pos.x = _window->getSize().x - 100 : pos.x;
                        pos.y > _window->getSize().y - 100 ? pos.y = _window->getSize().y - 100 : pos.y;
                        continue;
                    }
                    if ((masks[i].value() & physicPar) == physicPar)
                        pos.x <= -800 ? pos.x = 800 : pos.x;
                    else if (pos.x > _window->getSize().x || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
                        entityManager.removeMask(i);
                        componentManager.removeAllComponents(i);
                    }
                }
            }
        }
    }
}

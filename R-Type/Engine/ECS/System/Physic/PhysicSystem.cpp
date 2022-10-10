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
    Component &size = componentManager.getComponent(typeid(Size));

    if (con.getField(i).has_value()) {
        pos.x < 0 ? pos.x = 0 : pos.x;
        pos.y < 0 ? pos.y = 0 : pos.y;
        pos.x > _window->getSize().x - 100 ? pos.x = _window->getSize().x - 100 : pos.x;
        pos.y > _window->getSize().y - 100 ? pos.y = _window->getSize().y - 100 : pos.y;
        for (std::size_t j = 0; j < position.getSize(); j++) {
            if (position.getField(j).has_value() && enemy.getField(j).has_value()) {
                Position &pos2 = std::any_cast<Position &>(position.getField(j).value());
                Size &sz = std::any_cast<Size &>(size.getField(j).value());
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
    Component &proj = componentManager.getComponent(typeid(Projectile));
    Component &enemy = componentManager.getComponent(typeid(Enemy));
    Component &position = componentManager.getComponent(typeid(Position));
    Component &parent = componentManager.getComponent(typeid(Parent));
    Component &con = componentManager.getComponent(typeid(Controllable));
    Component &life = componentManager.getComponent(typeid(Life));
    Component &appear = componentManager.getComponent(typeid(Appearance));
    Component &size = componentManager.getComponent(typeid(Size));

    if (proj.getField(i).has_value() && parent.getField(i).has_value()) {
        Parent &par = std::any_cast<Parent &>(parent.getField(i).value());
        for (std::size_t j = 0; j < position.getSize(); j++) {
            if (position.getField(j).has_value() && (enemy.getField(j).has_value() || con.getField(j).has_value()) && par.id != j) {
                if (appear.getField(j).has_value() && std::any_cast<Appearance &>(appear.getField(j).value()).app)
                    continue;
                Position &pos2 = std::any_cast<Position &>(position.getField(j).value());
                Size &sz = std::any_cast<Size &>(size.getField(j).value());
                if (pos.x >= pos2.x && pos.x <= pos2.x + sz.x && pos.y >= pos2.y && pos.y <= pos2.y + sz.y) {
                    Life &hp = std::any_cast<Life &>(life.getField(j).value());
                    hp.life -= 1;
                    if (hp.life == 0) {
                        componentManager.removeAllComponents(j);
                        entityManager.removeMask(j);
                    }
                    componentManager.removeAllComponents(j);
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
    auto &masks = entityManager.getMasks();
    std::size_t physicSpeed = (InfoEntity::VEL | InfoEntity::POS);
    std::size_t physicControl = (InfoEntity::CONTROLLABLE | InfoEntity::POS);
    std::size_t physicPar = (InfoEntity::VEL | InfoEntity::POS | InfoEntity::PARALLAX);
    std::size_t physicPat = (InfoEntity::PATERN);
    std::size_t physicAppear = (InfoEntity::APP);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & physicSpeed) == physicSpeed) {
                Velocity &vel = std::any_cast<Velocity &>(componentManager.getComponent(typeid(Velocity)).getField(i).value());
                Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                if ((masks[i].value() & physicAppear) != physicAppear) {
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
                    if ((masks[i].value() & physicPar) != physicPar)
                        pos.x <= -800 ? pos.x = 800 : pos.x;
                    else if (pos.x > _window->getSize().x || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
                        entityManager.removeMask(i);
                        componentManager.removeAllComponents(i);
                    }
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
}

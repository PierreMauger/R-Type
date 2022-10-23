#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->_window = window;
}

void PhysicSystem::createBonus(std::size_t id, std::size_t drop, ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t addEntity = masks.size();
    std::size_t physicDrop = (InfoComp::SIZE1 | InfoComp::POS);

    if (masks[id].has_value() && (masks[id].value() & physicDrop) == physicDrop) {
        Size &size = componentManager.getSingleComponent<Size>(id);
        Position &pos = componentManager.getSingleComponent<Position>(id);
        entityManager.addManualMask(addEntity, (InfoComp::SPRITEID | InfoComp::POS | InfoComp::DROP | InfoComp::SIZE1), componentManager);
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{4, Priority::MEDIUM});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
        componentManager.getComponent(typeid(DropBonus)).emplaceData(addEntity, DropBonus{drop});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{55, 30});
    }
}

bool PhysicSystem::checkColision(Position &pos, Position &pos2, Size &sz, Size &sz2)
{
    this->_rect1 = sf::Rect(pos.x, pos.y, sz.x - 10, sz.y - 10);
    this->_rect2 = sf::Rect(pos2.x, pos2.y, sz2.x - 10, sz2.y - 10);

    return (this->_rect1.intersects(this->_rect2));
}

bool PhysicSystem::checkAppareance(ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel)
{
    Appearance &app = componentManager.getSingleComponent<Appearance>(i);
    if (app.app) {
        pos.y -= -vel.baseSpeed;
        if (pos.y >= app.end) {
            vel.y = 0;
            app.app = false;
        }
        return true;
    }
    return false;
}

bool PhysicSystem::collisionBonus(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicDrop = (InfoComp::SIZE1 | InfoComp::POS | InfoComp::DROP);
    std::size_t physicCont = (InfoComp::CONTROLLABLE | InfoComp::POS | InfoComp::SIZE1);

    if (!masks[i].has_value() || (masks[i].value() & physicCont) != physicCont)
        return false;
    Size &size = componentManager.getSingleComponent<Size>(i);
    for (std::size_t j = 0; j < masks.size(); j++) {
        if (masks[j].has_value() && ((masks[j].value() & physicDrop) == physicDrop)) {
            Size &size2 = componentManager.getSingleComponent<Size>(j);
            Position &pos2 = componentManager.getSingleComponent<Position>(j);
            DropBonus &drop = componentManager.getSingleComponent<DropBonus>(j);
            if (this->checkColision(pos, pos2, size, size2)) {
                componentManager.removeAllComponents(j);
                entityManager.removeMask(j);
                if (drop.id == 0)
                    componentManager.getSingleComponent<CooldownShoot>(i).shootDelay /= 2;
                if (drop.id == 1)
                    componentManager.getSingleComponent<CooldownShoot>(i).shootDelay += 1;
                return true;
            }
        }
    }
    return false;
}

bool PhysicSystem::collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicCon = (InfoComp::CONTROLLABLE);
    std::size_t physicCol = (InfoComp::POS | InfoComp::ENEMY | InfoComp::SIZE1);

    if (masks[i].has_value() && (masks[i].value() & physicCon) == physicCon) {
        for (std::size_t j = 0; j < masks.size(); j++) {
            if (masks[j].has_value() && (masks[j].value() & physicCol) == physicCol) {
                if (this->checkColision(pos, componentManager.getSingleComponent<Position>(j), componentManager.getSingleComponent<Size>(i),
                                        componentManager.getSingleComponent<Size>(j))) {
                    componentManager.removeAllComponents(i);
                    entityManager.removeMask(i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool PhysicSystem::collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicProj = (InfoComp::PROJECTILE | InfoComp::PARENT | InfoComp::POS);
    std::size_t physicApp = (InfoComp::APP);
    std::size_t physicCon = (InfoComp::CONTROLLABLE);
    std::size_t physicEne = (InfoComp::ENEMY);
    std::size_t physicDrop = (InfoComp::DROP);

    if (masks[i].has_value() && (masks[i].value() & physicProj) == physicProj) {
        Parent &par = componentManager.getSingleComponent<Parent>(i);
        for (std::size_t j = 0; j < masks.size(); j++) {
            if (masks[j].has_value() && ((masks[j].value() & physicCon) == physicCon || (masks[j].value() & physicEne) == physicEne) && par.id != j) {
                if (((masks[j].value() & physicApp) == physicApp && componentManager.getSingleComponent<Appearance>(j).app) ||
                    ((masks[j].value() & physicEne) == physicEne && (masks[par.id].value() & physicEne) == physicEne))
                    continue;
                if (this->checkColision(pos, componentManager.getSingleComponent<Position>(j), componentManager.getSingleComponent<Size>(i),
                                        componentManager.getSingleComponent<Size>(j))) {
                    Life &hp = componentManager.getSingleComponent<Life>(j);
                    Projectile &proj = componentManager.getSingleComponent<Projectile>(i);
                    if ((masks[par.id].value() & physicCon) == physicCon)
                        componentManager.getSingleComponent<Controllable>(par.id).kill++;
                    if (proj.damage >= hp.life) {
                        if ((masks[j].value() & physicDrop) == physicDrop)
                            this->createBonus(j, componentManager.getSingleComponent<DropBonus>(j).id, componentManager, entityManager);
                        hp.life = 0;
                        componentManager.removeAllComponents(j);
                        entityManager.removeMask(j);
                    } else
                        hp.life -= proj.damage;
                    componentManager.removeAllComponents(i);
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
    std::size_t physicSpeed = (InfoComp::VEL | InfoComp::POS);
    std::size_t physicControl = (InfoComp::CONTROLLABLE | InfoComp::POS | InfoComp::SIZE1);
    std::size_t physicPar = (InfoComp::VEL | InfoComp::POS | InfoComp::PARALLAX);
    std::size_t physicPat = (InfoComp::PATERN);
    std::size_t physicAppear = (InfoComp::APP);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & physicSpeed) == physicSpeed) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
            if ((masks[i].value() & physicAppear) == physicAppear && checkAppareance(componentManager, i, pos, vel))
                continue;
            if ((masks[i].value() & physicPar) == physicPar) {
                pos.x += vel.x;
                if (pos.x <= -static_cast<int>(_window->getSize().x))
                    pos.x = 0;
                continue;
            }
            if (pos.x > _window->getSize().x || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
                entityManager.removeMask(i);
                componentManager.removeAllComponents(i);
                continue;
            }
            if ((masks[i].value() & physicPat) != physicPat) {
                pos.x += vel.x;
                pos.y += vel.y;
                if (this->collisionFireball(i, componentManager, entityManager, pos))
                    continue;
                if (this->collisionEnemy(i, componentManager, entityManager, pos))
                    continue;
                if (this->collisionBonus(i, componentManager, entityManager, pos))
                    continue;
            }
            if ((masks[i].value() & physicControl) == physicControl) {
                Position &pos = componentManager.getSingleComponent<Position>(i);
                Size &size = componentManager.getSingleComponent<Size>(i);
                pos.x < 0 ? pos.x = 0 : pos.x;
                pos.y < 0 ? pos.y = 0 : pos.y;
                pos.x > _window->getSize().x - size.x ? pos.x = _window->getSize().x - size.x : pos.x;
                pos.y > _window->getSize().y - size.y ? pos.y = _window->getSize().y - size.y : pos.y;
            }
        }
    }
}

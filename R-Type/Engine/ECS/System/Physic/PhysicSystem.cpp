#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(Graphic &graphic, [[maybe_unused]] EntityManager &entityManager)
{
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
    this->_syncId = graphic.getSyncId();
    this->_clock = graphic.getClock();

    entityManager.addMaskCategory(this->_speedTag);
    entityManager.addMaskCategory(this->_shieldTag);
    entityManager.addMaskCategory(this->_dropTag);
}

void PhysicSystem::switchCreateBonus(std::size_t addEntity, std::size_t drop, ComponentManager &componentManager, Size &size, Position &pos)
{
    sf::Vector2f sizeBonus{3 / _screenSize->x * this->_window->getSize().x, 3 / _screenSize->y * this->_window->getSize().y};

    switch (drop) {
    case 0:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_SIZE, Priority::MEDIUM, 0, 5, true, false, 0, 0.05, 24, 0});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 24, 16}, sf::Color::White, {sizeBonus.x, sizeBonus.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{23 * sizeBonus.x, 16 * sizeBonus.y});
        break;

    case 1:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_SPEED, Priority::MEDIUM, 0, 5, true, false, 0, 0.05, 30, 0});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 30, 22}, sf::Color::White, {sizeBonus.x, sizeBonus.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{30 * sizeBonus.x, 22 * sizeBonus.y});
        break;

    case 2:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_SHIELD, Priority::MEDIUM, 0, 14, false, false, 0, 0.05, 32, 0});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 32, 32}, sf::Color::White, {sizeBonus.x, sizeBonus.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{32 * sizeBonus.x, 32 * sizeBonus.y});
        break;
    case 3:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_TRIPLE, Priority::MEDIUM, 0, 3, true, false, 0, 0.05, 32, 0});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 32, 32}, sf::Color::White, {sizeBonus.x, sizeBonus.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x, pos.y});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{32 * sizeBonus.x, 32 * sizeBonus.y});
        break;

    default:
        break;
    }
}

void PhysicSystem::createBonus(std::size_t id, std::size_t drop, ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t physicDrop = (InfoComp::SIZE | InfoComp::POS);

    if (entityManager.hasMask(id, physicDrop)) {
        Size &size = componentManager.getSingleComponent<Size>(id);
        Position &pos = componentManager.getSingleComponent<Position>(id);
        std::size_t addEntity = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::DROP | InfoComp::SIZE | InfoComp::SPRITEAT | InfoComp::SYNCID), componentManager);
        this->switchCreateBonus(addEntity, drop, componentManager, size, pos);
        componentManager.getComponent(typeid(DropBonus)).emplaceData(addEntity, DropBonus{drop});
        if (this->_syncId) {
            componentManager.getComponent(typeid(SyncID)).emplaceData(addEntity, SyncID{*this->_syncId});
            *this->_syncId += 1;
        }
        addEntity = entityManager.addMask((InfoComp::SOUNDID | InfoComp::SYNCID), componentManager);
        componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{A_BONUS, false, false});
        if (this->_syncId) {
            componentManager.getComponent(typeid(SyncID)).emplaceData(addEntity, SyncID{*this->_syncId});
            *this->_syncId += 1;
        }
    }
}

bool PhysicSystem::checkCollision(Position pos, Position pos2, Size sz, Size sz2)
{
    sf::Rect<float> rect1 = sf::Rect(pos.x, pos.y, sz.x, sz.y);
    sf::Rect<float> rect2 = sf::Rect(pos2.x, pos2.y, sz2.x, sz2.y);

#ifndef NDEBUG
    sf::RectangleShape rect3{sf::Vector2f{sz.x, sz.y}};
    sf::RectangleShape rect4{sf::Vector2f{sz2.x, sz2.y}};
    rect3.setPosition(pos.x, pos.y);
    rect4.setPosition(pos2.x, pos2.y);
    rect3.setOutlineThickness(2);
    rect4.setOutlineThickness(2);
    rect3.setOutlineColor(sf::Color::Red);
    rect4.setOutlineColor(sf::Color::Red);
    this->_window->draw(rect3);
    this->_window->draw(rect4);
#endif
    return rect1.intersects(rect2);
}

bool PhysicSystem::checkAppareance(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, Position &pos, Velocity &vel)
{
    Appearance &app = componentManager.getSingleComponent<Appearance>(i);
    SpriteAttribut &sprite = componentManager.getSingleComponent<SpriteAttribut>(i);

    if (app.app) {
        if (app.delay != 0 && this->_clock->getElapsedTime().asSeconds() - app.delay < app.invincible) {
            pos.y += vel.y;
            pos.x += vel.x;
            this->physicVessel(componentManager, entityManager, i);
            return true;
        }
        if (app.x_app != 0.0f && pos.x > app.x_app) {
            pos.x -= vel.x;
            return true;
        } else
            vel.x = 0;
        pos.y -= -vel.baseSpeedY;
        if (sprite.color.a != 50)
            sprite.color = sf::Color(255, 255, 255, 50);
        if (pos.y >= app.end) {
            vel.y = 0;
            if (app.invincible == 0) {
                app.app = false;
                sprite.color = sf::Color(255, 255, 255, 255);
                return true;
            }
            if (app.delay == 0 && app.invincible != 0)
                app.delay = this->_clock->getElapsedTime().asSeconds();
            if (app.invincible != 0 && this->_clock->getElapsedTime().asSeconds() - app.delay >= app.invincible) {
                app.app = false;
                app.delay = 0;
                sprite.color = sf::Color(255, 255, 255, 255);
            }
        }
        return true;
    }
    return false;
}

void PhysicSystem::killWhenDisappeared(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, std::size_t &it)
{
    if (entityManager.hasMask(i, InfoComp::CONTROLLABLE)) {
        componentManager.getSingleComponent<Appearance>(i).app = true;
        componentManager.getSingleComponent<Appearance>(i).end = 100 / _screenSize->y * _window->getSize().y;
        componentManager.getSingleComponent<Position>(i).x = 10;
        componentManager.getSingleComponent<Position>(i).y = 28 / _screenSize->y * _window->getSize().y * -1;
        componentManager.getSingleComponent<Controllable>(i).kill = 0;
        componentManager.getSingleComponent<Controllable>(i).death += 1;
        componentManager.getSingleComponent<SpriteAttribut>(i).rotation = 0;
        for (auto j : entityManager.getMaskCategory(this->_shieldTag)) {
            if (componentManager.getSingleComponent<Parent>(j).id == componentManager.getSingleComponent<SyncID>(i).id) {
                componentManager.removeAllComponents(j);
                entityManager.removeMask(j);
            }
        }
    } else {
        componentManager.removeAllComponents(i);
        entityManager.removeMask(i);
        it--;
    }
}

bool PhysicSystem::checkDisappearance(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel, std::size_t &it)
{
    Disappearance &dis = componentManager.getSingleComponent<Disappearance>(i);
    SpriteAttribut &sprite = componentManager.getSingleComponent<SpriteAttribut>(i);

    if (dis.dis) {
        pos.y -= -vel.baseSpeedY * 3;
        sprite.rotation += 40;
        if (pos.y >= dis.end) {
            vel.y = 0;
            dis.dis = false;
            this->killWhenDisappeared(entityManager, componentManager, i, it);
        }
        return true;
    }
    return false;
}

void PhysicSystem::bonusFound(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, DropBonus drop, Size size)
{
    bool checkShield = false;

    componentManager.removeAllComponents(j);
    entityManager.removeMask(j);
    if (drop.id == 0)
        componentManager.getSingleComponent<CooldownShoot>(i).shootDelay = 0.5;
    if (drop.id == 1)
        componentManager.getSingleComponent<CooldownShoot>(i).size < 3 ? componentManager.getSingleComponent<CooldownShoot>(i).size += 1 : 0;
    if (drop.id == 3)
        componentManager.getSingleComponent<CooldownShoot>(i).tripleShoot += 2;
    if (drop.id == 2) {
        for (auto k : entityManager.getMaskCategory(this->_shieldTag)) {
            if (componentManager.getSingleComponent<Parent>(k).id == componentManager.getSingleComponent<SyncID>(i).id) {
                checkShield = true;
                componentManager.getSingleComponent<Shield>(k).life = componentManager.getSingleComponent<Shield>(k).defaultLife;
                break;
            }
        }
        if (!checkShield) {
            std::size_t idShield = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::SHIELD), componentManager);
            componentManager.getComponent(typeid(SpriteID)).emplaceData(idShield, SpriteID{S_SHIELD, Priority::MEDIUM});
            componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(idShield, SpriteAttribut{0, {0, 0, 700, 440}, sf::Color::White, {size.x / _screenSize->x * this->_window->getSize().x, size.y / _screenSize->y * this->_window->getSize().y}, {700 / 2, 440 / 2}});
            componentManager.getComponent(typeid(Position)).emplaceData(idShield, Position{0, 0, 0});
            componentManager.getComponent(typeid(Shield)).emplaceData(idShield, Shield{5});
            if (this->_syncId) {
                componentManager.getComponent(typeid(SyncID)).emplaceData(idShield, SyncID{*this->_syncId});
                *this->_syncId += 1;
            }
            componentManager.getComponent(typeid(Parent)).emplaceData(idShield, Parent{componentManager.getSingleComponent<SyncID>(idShield).id});
        }
    }
}

bool PhysicSystem::collisionBonus(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position pos)
{
    std::size_t physicCont = (InfoComp::CONTROLLABLE | InfoComp::POS | InfoComp::SIZE);

    if (!entityManager.hasMask(i, physicCont))
        return false;
    Size size = componentManager.getSingleComponent<Size>(i);
    for (auto j : entityManager.getMaskCategory(this->_dropTag)) {
        Size size2 = componentManager.getSingleComponent<Size>(j);
        Position pos2 = componentManager.getSingleComponent<Position>(j);
        DropBonus drop = componentManager.getSingleComponent<DropBonus>(j);
        if (this->checkCollision(pos, pos2, size, size2)) {
            this->bonusFound(componentManager, entityManager, i, j, drop, size);
            return true;
        }
    }
    return false;
}

bool PhysicSystem::collisionEnemySplit(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Position pos, std::size_t &it)
{
    std::size_t physicCol = (InfoComp::POS | InfoComp::ENEMY | InfoComp::SIZE);

    if (entityManager.hasMask(j, physicCol) && this->checkCollision(pos, componentManager.getSingleComponent<Position>(j), componentManager.getSingleComponent<Size>(i), componentManager.getSingleComponent<Size>(j))) {
        if (entityManager.hasMask(i, InfoComp::DIS))
            componentManager.getSingleComponent<Disappearance>(i).dis = true;
        else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
            it--;
        }
        return true;
    }
    return false;
}

bool PhysicSystem::collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position pos, std::size_t &it)
{
    auto &masks = entityManager.getMasks();

    if (entityManager.hasMask(i, InfoComp::CONTROLLABLE))
        for (std::size_t j = 0; j < masks.size(); j++)
            if (this->collisionEnemySplit(componentManager, entityManager, i, j, pos, it))
                return true;
    return false;
}

void PhysicSystem::collisionFireballEnemy(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, bool &checkShield)
{
    Life &hp = componentManager.getSingleComponent<Life>(j);
    Projectile proj = componentManager.getSingleComponent<Projectile>(i);

    for (auto k : entityManager.getMaskCategory(this->_shieldTag)) {
        if (componentManager.getSingleComponent<Parent>(k).id == componentManager.getSingleComponent<SyncID>(j).id) {
            Shield &shield = componentManager.getSingleComponent<Shield>(k);
            if (proj.damage >= shield.life) {
                hp.life -= proj.damage - shield.life;
                shield.life = 0;
            } else
                shield.life -= proj.damage;
            checkShield = true;
            break;
        }
    }
}

void PhysicSystem::collisionCheckShield(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j)
{
    Life &hp = componentManager.getSingleComponent<Life>(j);
    Projectile proj = componentManager.getSingleComponent<Projectile>(i);
    std::size_t idPar = entityManager.getBySyncId(componentManager.getSingleComponent<Parent>(i).id, componentManager);

    if (proj.damage >= hp.life) {
        if (entityManager.hasMask(j, InfoComp::DROP))
            this->createBonus(j, componentManager.getSingleComponent<DropBonus>(j).id, componentManager, entityManager);
        hp.life = 0;
        if (entityManager.hasMask(idPar, InfoComp::CONTROLLABLE))
            componentManager.getSingleComponent<Controllable>(idPar).kill++;
        if (entityManager.hasMask(j, InfoComp::DIS))
            componentManager.getSingleComponent<Disappearance>(j).dis = true;
        else {
            componentManager.removeAllComponents(j);
            entityManager.removeMask(j);
        }
    } else
        hp.life -= proj.damage;
}

bool PhysicSystem::splitCollisionFireball(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Position pos, std::size_t &it)
{
    Parent par = componentManager.getSingleComponent<Parent>(i);
    std::size_t idPar = entityManager.getBySyncId(par.id, componentManager);
    bool checkShield = false;

    if ((entityManager.hasMask(j, InfoComp::CONTROLLABLE) || entityManager.hasMask(j, InfoComp::ENEMY)) && idPar != j) {
        if ((entityManager.hasMask(j, InfoComp::APP) && componentManager.getSingleComponent<Appearance>(j).app) || (entityManager.hasMask(j, InfoComp::DIS) && componentManager.getSingleComponent<Disappearance>(j).dis) ||
            (entityManager.hasMask(j, InfoComp::ENEMY) && entityManager.hasMask(idPar, InfoComp::ENEMY)))
            return false;
        if (this->checkCollision(pos, componentManager.getSingleComponent<Position>(j), componentManager.getSingleComponent<Size>(i), componentManager.getSingleComponent<Size>(j))) {
            if (!entityManager.hasMask(j, InfoComp::LIFE)) {
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
                it--;
                return true;
            }
            this->collisionFireballEnemy(componentManager, entityManager, i, j, checkShield);
            if (!checkShield)
                this->collisionCheckShield(componentManager, entityManager, i, j);
            if (entityManager.hasMask(i, InfoComp::DIS))
                componentManager.getSingleComponent<Disappearance>(i).dis = true;
            else {
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
                it--;
            }
            return true;
        }
    }
    return false;
}

bool PhysicSystem::collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position pos, std::size_t &it)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicProj = (InfoComp::PROJECTILE | InfoComp::PARENT | InfoComp::POS);

    if (!entityManager.hasMask(i, physicProj))
        return false;
    Parent par = componentManager.getSingleComponent<Parent>(i);
    std::size_t idPar = entityManager.getBySyncId(par.id, componentManager);
    if ((idPar >= masks.size() || !masks[idPar].has_value())) {
        componentManager.removeAllComponents(i);
        entityManager.removeMask(i);
        it--;
        return false;
    }
    for (std::size_t j = 0; j < masks.size(); j++)
        if (this->splitCollisionFireball(componentManager, entityManager, i, j, pos, it))
            return true;
    return false;
}

void PhysicSystem::physicVessel(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i)
{
    std::size_t physicControl = (InfoComp::CONTROLLABLE | InfoComp::POS | InfoComp::SIZE);

    if (entityManager.hasMask(i, physicControl)) {
        Position &pos = componentManager.getSingleComponent<Position>(i);
        Size size = componentManager.getSingleComponent<Size>(i);
        pos.x < 0 ? pos.x = 0 : pos.x;
        pos.y < 0 ? pos.y = 0 : pos.y;
        pos.x > _window->getSize().x - size.x ? pos.x = _window->getSize().x - size.x : pos.x;
        pos.y > _window->getSize().y - size.y ? pos.y = _window->getSize().y - size.y : pos.y;
    }
}

void PhysicSystem::physicPattern(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i)
{
    if (entityManager.hasMask(i, InfoComp::PATTERN)) {
        Position &pos = componentManager.getSingleComponent<Position>(i);
        Size size = componentManager.getSingleComponent<Size>(i);
        pos.y < 0 ? pos.y = 0 : pos.y;
        pos.y > _window->getSize().y - size.y ? pos.y = _window->getSize().y - size.y : pos.y;
    }
}

bool PhysicSystem::physicAnim(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t &it, Position &pos, Velocity &vel)
{
    std::size_t physicPar = (InfoComp::VEL | InfoComp::POS | InfoComp::PARALLAX);

    if (entityManager.hasMask(i, InfoComp::APP) && checkAppareance(componentManager, entityManager, i, pos, vel))
        return true;
    if (entityManager.hasMask(i, InfoComp::DIS) && checkDisappearance(entityManager, componentManager, i, pos, vel, it))
        return true;
    if (entityManager.hasMask(i, physicPar)) {
        pos.x += vel.x;
        if (pos.x <= -static_cast<int>(this->_window->getSize().x))
            pos.x = 0;
        return true;
    }
    pos.y += vel.y;
    pos.x += vel.x;
    if ((entityManager.hasMask(i, InfoComp::PROJECTILE) && pos.x > _window->getSize().x + 100) || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
        entityManager.removeMask(i);
        componentManager.removeAllComponents(i);
        it--;
        return true;
    }
    return false;
}

bool PhysicSystem::physicCollision(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, Position pos, std::size_t &it)
{
    if (!entityManager.hasMask(i, InfoComp::PATTERN)) {
        if (this->collisionEnemy(i, componentManager, entityManager, pos, it))
            return true;
        if (this->collisionBonus(i, componentManager, entityManager, pos))
            return true;
        if (this->collisionFireball(i, componentManager, entityManager, pos, it))
            return true;
    }
    return false;
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    for (std::size_t i = 0; i < entityManager.getMaskCategory(this->_speedTag).size(); i++) {
        std::size_t id = entityManager.getMaskCategory(this->_speedTag)[i];
        if (!entityManager.hasMask(id, this->_speedTag))
            continue;
        Position &pos = componentManager.getSingleComponent<Position>(id);
        Velocity vel = componentManager.getSingleComponent<Velocity>(id);
        if (this->physicAnim(componentManager, entityManager, id, i, pos, vel))
            continue;
        if (this->physicCollision(componentManager, entityManager, id, pos, i))
            continue;
        this->physicVessel(componentManager, entityManager, id);
        this->physicPattern(componentManager, entityManager, id);
    }
}

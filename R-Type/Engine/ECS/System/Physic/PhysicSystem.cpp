#include "Engine/ECS/System/Physic/PhysicSystem.hpp"

using namespace eng;

PhysicSystem::PhysicSystem(Graphic &graphic, [[maybe_unused]] EntityManager &entityManager, std::shared_ptr<std::size_t> syncId)
{
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
    this->_syncId = syncId;

    entityManager.addMaskCategory(this->_speedTag);
    entityManager.addMaskCategory(this->_shieldTag);
    entityManager.addMaskCategory(this->_dropTag);
}

void PhysicSystem::switchCreateBonus(std::size_t addEntity, std::size_t drop, ComponentManager &componentManager, Size &size, Position &pos)
{
    sf::Vector2f sizeBonus{_screenSize->x / (1920 / 3), _screenSize->y / (1080 / 3)};

    switch (drop) {
    case 0:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_SHOOT_SIZE, Priority::MEDIUM});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 18, 16}, sf::Color::White, {sizeBonus.x / _screenSize->x * _window->getSize().x, sizeBonus.y / _screenSize->y * _window->getSize().y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{18 * sizeBonus.x, 16 * sizeBonus.y});
        break;

    case 1:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_SPEED, Priority::MEDIUM});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 18, 16}, sf::Color::White, {sizeBonus.x / _screenSize->x * _window->getSize().x, sizeBonus.y / _screenSize->y * _window->getSize().y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{18 * sizeBonus.x, 16 * sizeBonus.y});
        break;

    case 2:
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_BONUS_SHIELD, Priority::MEDIUM, 0, 14, false, false, 0, 0.05, 32, 0});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 32, 32}, sf::Color::White, {sizeBonus.x / _screenSize->x * _window->getSize().x, sizeBonus.y / _screenSize->y * _window->getSize().y}});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{32 * sizeBonus.x / _screenSize->x * _window->getSize().x, 32 * sizeBonus.y / _screenSize->y * _window->getSize().y});
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
        componentManager.getComponent(typeid(SyncID)).emplaceData(addEntity, SyncID{this->_syncId ? *(this->_syncId.get()) : 0});
        addEntity = entityManager.addMask((InfoComp::SOUNDID | InfoComp::SYNCID), componentManager);
        componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{0, false, false});
        componentManager.getComponent(typeid(SyncID)).emplaceData(addEntity, SyncID{this->_syncId ? *(this->_syncId.get()) : 0});
    }
}

bool PhysicSystem::checkCollision(Position pos, Position pos2, Size sz, Size sz2)
{
    sf::Rect<float> rect1 = sf::Rect(pos.x, pos.y, sz.x, sz.y);
    sf::Rect<float> rect2 = sf::Rect(pos2.x, pos2.y, sz2.x, sz2.y);

    return rect1.intersects(rect2);
}

bool PhysicSystem::checkAppareance(ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel)
{
    Appearance &app = componentManager.getSingleComponent<Appearance>(i);
    SpriteAttribut &sprite = componentManager.getSingleComponent<SpriteAttribut>(i);
    if (app.app) {
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
            app.app = false;
            sprite.color = sf::Color::White;
        }
        return true;
    }
    return false;
}

void PhysicSystem::killWhenDisappeared(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i)
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
    }
}

bool PhysicSystem::checkDisappearance(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel)
{
    Disappearance &dis = componentManager.getSingleComponent<Disappearance>(i);
    SpriteAttribut &sprite = componentManager.getSingleComponent<SpriteAttribut>(i);

    if (dis.dis) {
        pos.y -= -vel.baseSpeedY * 3;
        sprite.rotation += 40;
        if (pos.y >= dis.end) {
            vel.y = 0;
            dis.dis = false;
            this->killWhenDisappeared(entityManager, componentManager, i);
        }
        return true;
    }
    return false;
}

void PhysicSystem::bonusFound(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, DropBonus &drop, Size &size)
{
    auto &masks = entityManager.getMasks();
    bool checkShield = false;

    componentManager.removeAllComponents(j);
    entityManager.removeMask(j);
    if (drop.id == 0)
        componentManager.getSingleComponent<CooldownShoot>(i).shootDelay /= 2 > 0.1 ? componentManager.getSingleComponent<CooldownShoot>(i).shootDelay /= 2 : 0;
    if (drop.id == 1)
        componentManager.getSingleComponent<CooldownShoot>(i).size < 3 ? componentManager.getSingleComponent<CooldownShoot>(i).size += 1 : 0;
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
            componentManager.getComponent(typeid(SyncID)).emplaceData(idShield, SyncID{this->_syncId ? *(this->_syncId.get()) : 0});
            componentManager.getComponent(typeid(Parent)).emplaceData(idShield, Parent{componentManager.getSingleComponent<SyncID>(idShield).id});
        }
    }
}

bool PhysicSystem::collisionBonus(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    std::size_t physicCont = (InfoComp::CONTROLLABLE | InfoComp::POS | InfoComp::SIZE);

    if (!entityManager.hasMask(i, physicCont))
        return false;
    Size &size = componentManager.getSingleComponent<Size>(i);
    for (auto j : entityManager.getMaskCategory(this->_dropTag)) {
        Size &size2 = componentManager.getSingleComponent<Size>(j);
        Position &pos2 = componentManager.getSingleComponent<Position>(j);
        DropBonus &drop = componentManager.getSingleComponent<DropBonus>(j);
        if (this->checkCollision(pos, pos2, size, size2)) {
            this->bonusFound(componentManager, entityManager, i, j, drop, size);
            return true;
        }
    }
    return false;
}

bool PhysicSystem::collisionEnemySplit(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Position &pos)
{
    std::size_t physicCol = (InfoComp::POS | InfoComp::ENEMY | InfoComp::SIZE);
    std::size_t physicDis = (InfoComp::DIS);

    if (entityManager.hasMask(j, physicCol) && this->checkCollision(pos, componentManager.getSingleComponent<Position>(j), componentManager.getSingleComponent<Size>(i), componentManager.getSingleComponent<Size>(j))) {
        if (entityManager.hasMask(i, physicDis))
            componentManager.getSingleComponent<Disappearance>(i).dis = true;
        else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
        }
        return true;
    }
    return false;
}

bool PhysicSystem::collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicCon = (InfoComp::CONTROLLABLE);

    if (entityManager.hasMask(i, physicCon))
        for (std::size_t j = 0; j < masks.size(); j++)
            if (this->collisionEnemySplit(componentManager, entityManager, i, j, pos))
                return true;
    return false;
}

void PhysicSystem::checkFireballDamage(std::size_t i, std::size_t j, ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t physicDis = (InfoComp::DIS);
    std::size_t physicCon = (InfoComp::CONTROLLABLE);
    std::size_t physicDrop = (InfoComp::DROP);
    Life &hp = componentManager.getSingleComponent<Life>(j);
    Projectile &proj = componentManager.getSingleComponent<Projectile>(i);
    Parent &par = componentManager.getSingleComponent<Parent>(i);

    if (entityManager.hasMask(par.id, physicCon))
        componentManager.getSingleComponent<Controllable>(par.id).kill++;
    if (proj.damage >= hp.life) {
        if (entityManager.hasMask(j, physicDrop))
            this->createBonus(j, componentManager.getSingleComponent<DropBonus>(j).id, componentManager, entityManager);
        hp.life = 0;
        if (entityManager.hasMask(j, physicDis))
            componentManager.getSingleComponent<Disappearance>(j).dis = true;
        else {
            componentManager.removeAllComponents(j);
            entityManager.removeMask(j);
        }
    } else
        hp.life -= proj.damage;
    if (entityManager.hasMask(i, physicDis))
        componentManager.getSingleComponent<Disappearance>(i).dis = true;
    else {
        componentManager.removeAllComponents(i);
        entityManager.removeMask(i);
    }
}

void PhysicSystem::collisionFireballEnemy(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Parent par, bool &checkShield)
{
    std::size_t physicCon = (InfoComp::CONTROLLABLE);

    Life &hp = componentManager.getSingleComponent<Life>(j);
    Projectile &proj = componentManager.getSingleComponent<Projectile>(i);
    if (entityManager.hasMask(par.id, physicCon))
        componentManager.getSingleComponent<Controllable>(par.id).kill++;

    for (auto k : entityManager.getMaskCategory(this->_shieldTag)) {
        if (componentManager.getSingleComponent<Parent>(k).id == componentManager.getSingleComponent<SyncID>(j).id) {
            Shield &shield = componentManager.getSingleComponent<Shield>(k);
            if (proj.damage >= shield.life) {
                hp.life -= proj.damage - shield.life;
                shield.life = 0;
            } else {
                shield.life -= proj.damage;
            }
            checkShield = true;
            break;
        }
    }
}

void PhysicSystem::collisionCheckShield(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, bool &checkShield)
{
    std::size_t physicDrop = (InfoComp::DROP);
    std::size_t physicDis = (InfoComp::DIS);

    if (checkShield)
        return;
    Life &hp = componentManager.getSingleComponent<Life>(j);
    Projectile &proj = componentManager.getSingleComponent<Projectile>(i);
    if (proj.damage >= hp.life) {
        if (entityManager.hasMask(j, physicDrop))
            this->createBonus(j, componentManager.getSingleComponent<DropBonus>(j).id, componentManager, entityManager);
        hp.life = 0;
        if (entityManager.hasMask(j, physicDis))
            componentManager.getSingleComponent<Disappearance>(j).dis = true;
        else {
            componentManager.removeAllComponents(j);
            entityManager.removeMask(j);
        }
    } else
        hp.life -= proj.damage;
}

bool PhysicSystem::splitCollisionFireball(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Position &pos)
{
    std::size_t physicApp = (InfoComp::APP);
    std::size_t physicEne = (InfoComp::ENEMY);
    std::size_t physicCon = (InfoComp::CONTROLLABLE);
    std::size_t physicDis = (InfoComp::DIS);
    bool checkShield = false;
    Parent &par = componentManager.getSingleComponent<Parent>(i);

    if ((entityManager.hasMask(j, physicCon) || entityManager.hasMask(j, physicEne)) && par.id != j) {
        if ((entityManager.hasMask(j, physicApp) && componentManager.getSingleComponent<Appearance>(j).app) || (entityManager.hasMask(j, physicDis) && componentManager.getSingleComponent<Disappearance>(j).dis) || (entityManager.hasMask(j, physicEne) && entityManager.hasMask(par.id, physicEne)))
            return false;
        if (this->checkCollision(pos, componentManager.getSingleComponent<Position>(j), componentManager.getSingleComponent<Size>(i), componentManager.getSingleComponent<Size>(j))) {
            if (!entityManager.hasMask(j, InfoComp::LIFE)) {
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
                return true;
            }
            this->collisionFireballEnemy(componentManager, entityManager, i, j, par, checkShield);
            this->collisionCheckShield(componentManager, entityManager, i, j, checkShield);
            if (entityManager.hasMask(i, physicDis))
                componentManager.getSingleComponent<Disappearance>(i).dis = true;
            else {
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
            }
            return true;
        }
    }
    return false;
}

bool PhysicSystem::collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos)
{
    auto &masks = entityManager.getMasks();
    std::size_t physicProj = (InfoComp::PROJECTILE | InfoComp::PARENT | InfoComp::POS);

    if (!entityManager.hasMask(i, physicProj))
        return false;
    Parent &par = componentManager.getSingleComponent<Parent>(i);
    if (!masks[par.id].has_value()) {
        componentManager.removeAllComponents(i);
        entityManager.removeMask(i);
        return false;
    }
    for (std::size_t j = 0; j < masks.size(); j++)
        if (this->splitCollisionFireball(componentManager, entityManager, i, j, pos))
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
    std::size_t physicPat = (InfoComp::PATTERN);

    if (entityManager.hasMask(i, physicPat)) {
        Position &pos = componentManager.getSingleComponent<Position>(i);
        Size size = componentManager.getSingleComponent<Size>(i);
        pos.y < 0 ? pos.y = 0 : pos.y;
        pos.y > _window->getSize().y - size.y ? pos.y = _window->getSize().y - size.y : pos.y;
    }
}

bool PhysicSystem::physicAnim(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, Position &pos, Velocity &vel)
{
    std::size_t physicAppear = (InfoComp::APP);
    std::size_t physicDis = (InfoComp::DIS);
    std::size_t physicPar = (InfoComp::VEL | InfoComp::POS | InfoComp::PARALLAX);

    if (entityManager.hasMask(i, physicAppear) && checkAppareance(componentManager, i, pos, vel))
        return true;
    if (entityManager.hasMask(i, physicDis) && checkDisappearance(entityManager, componentManager, i, pos, vel))
        return true;
    if (entityManager.hasMask(i, physicPar)) {
        pos.x += vel.x;
        if (pos.x <= -static_cast<int>(this->_window->getSize().x))
            pos.x = 0;
        return true;
    }
    if ((entityManager.hasMask(i, InfoComp::PROJECTILE) && pos.x > _window->getSize().x + 100) || pos.y > _window->getSize().y || pos.x < -100 || pos.y < -100) {
        entityManager.removeMask(i);
        componentManager.removeAllComponents(i);
        return true;
    }
    return false;
}

bool PhysicSystem::physicCollision(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, Position &pos)
{
    if (!entityManager.hasMask(i, InfoComp::PATTERN)) {
        if (this->collisionEnemy(i, componentManager, entityManager, pos))
            return true;
        if (this->collisionBonus(i, componentManager, entityManager, pos))
            return true;
        if (this->collisionFireball(i, componentManager, entityManager, pos))
            return true;
    }
    return false;
}

void PhysicSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    for (auto id : entityManager.getMaskCategory(this->_speedTag)) {
        Position &pos = componentManager.getSingleComponent<Position>(id);
        Velocity vel = componentManager.getSingleComponent<Velocity>(id);
        if (this->physicAnim(componentManager, entityManager, id, pos, vel))
            continue;
        pos.y += vel.y;
        pos.x += vel.x;
        if (this->physicCollision(componentManager, entityManager, id, pos))
            continue;
        this->physicVessel(componentManager, entityManager, id);
        this->physicPattern(componentManager, entityManager, id);
    }
}

#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"

using namespace eng;

void ProjectilePreload::createTripleShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, std::size_t id, ProjectileStats projectile)
{
    std::size_t sizeMask = (InfoComp::SIZE | InfoComp::COOLDOWNSHOOT | InfoComp::POS);
    Size size = {0, 0};
    CooldownShoot sizeProj = {0, 0};
    Position pos = {0, 0};

    bool enemy = entityManager.hasMask(id, InfoComp::ENEMY);
    sf::Vector2f sizeFire = sf::Vector2f(56 / screenSize->x * windowsSize.x, 32 / screenSize->y * windowsSize.y);

    if (entityManager.hasMask(id, sizeMask)) {
        size = componentManager.getSingleComponent<Size>(id);
        sizeProj = componentManager.getSingleComponent<CooldownShoot>(id);
        pos = componentManager.getSingleComponent<Position>(id);
    }
    for (int i = 0; i != static_cast<int>(projectile.tripleShoot); i++) {
        std::size_t addEntity = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::SIZE | InfoComp::SPRITEAT), componentManager);
        if (enemy)
            componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_REV_FIREBALL, Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 56, 0});
        else
            componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((projectile.damage == 2) ? 4 : 3), Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 56, 0});
        componentManager.getComponent(typeid(SpriteAttribut))
            .emplaceData(addEntity, SpriteAttribut{projectile.rotation,
                                                   {0, 0, 56, 32},
                                                   sf::Color::White,
                                                   {(sizeProj.size / screenSize->x * windowsSize.x), (sizeProj.size / screenSize->y * windowsSize.y)},
                                                   (projectile.rotation != 0 ? sf::Vector2f{sizeFire.x * sizeProj.size / 2, sizeFire.y * sizeProj.size / 2} : sf::Vector2f{0, 0})});
        componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x, (pos.y + (size.y / 2)) - (sizeFire.y * sizeProj.size / 2), pos.z});
        componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{projectile.velX / screenSize->x * windowsSize.x, static_cast<float>((i % 2 == 0) ? i + 1 : -i), 0});
        componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
        componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, projectile.damage, sizeProj.size});
        componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{sizeFire.x * sizeProj.size, sizeFire.y * sizeProj.size});
    }
}

void ProjectilePreload::createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, std::size_t id, ProjectileStats projectile)
{
    std::size_t sizeMask = (InfoComp::SIZE | InfoComp::COOLDOWNSHOOT | InfoComp::POS);
    Size size = {0, 0};
    CooldownShoot sizeProj = {0, 0};
    Position pos = {0, 0};

    bool enemy = entityManager.hasMask(id, InfoComp::ENEMY);
    sf::Vector2f sizeFire = sf::Vector2f(56 / screenSize->x * windowsSize.x, 32 / screenSize->y * windowsSize.y);
    std::size_t addEntity = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::SIZE | InfoComp::SPRITEAT), componentManager);

    if (entityManager.hasMask(id, sizeMask)) {
        size = componentManager.getSingleComponent<Size>(id);
        sizeProj = componentManager.getSingleComponent<CooldownShoot>(id);
        pos = componentManager.getSingleComponent<Position>(id);
    }
    if (enemy)
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{S_REV_FIREBALL, Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 56, 0});
    else
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((projectile.damage == 2) ? 4 : 3), Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 56, 0});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(
            addEntity,
            SpriteAttribut{
                projectile.rotation, {0, 0, 56, 32}, sf::Color::White, {(sizeProj.size / screenSize->x * windowsSize.x), (sizeProj.size / screenSize->y * windowsSize.y)}, (projectile.rotation != 0 ? sf::Vector2f{sizeFire.x * sizeProj.size / 2, sizeFire.y * sizeProj.size / 2} : sf::Vector2f{0, 0})});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x, (pos.y + (size.y / 2)) - (sizeFire.y * sizeProj.size / 2), pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{(windowsSize.x / (screenSize->x / projectile.velX)), (windowsSize.y / (screenSize->y / projectile.velY)), 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, projectile.damage, sizeProj.size});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{sizeFire.x * sizeProj.size, sizeFire.y * sizeProj.size});
    if (!enemy) {
        addEntity = entityManager.addMask((InfoComp::SOUNDID), componentManager);
        float pitch = (sizeProj.size == 1) ? 1 : (1 - (sizeProj.size / 10)) < 0.2 ? 0.2 : (1 - (sizeProj.size / 10));
        componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{4, false, false, pitch});
    }
    if (projectile.tripleShoot != 0)
        createTripleShoot(entityManager, componentManager, windowsSize, screenSize, id, projectile);
}

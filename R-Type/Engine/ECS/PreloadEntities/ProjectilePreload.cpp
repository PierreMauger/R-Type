#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"

void eng::ProjectilePreload::createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize,
                                         std::shared_ptr<sf::Vector2f> screenSize, std::size_t id, std::size_t damage)
{
    auto &masks = entityManager.getMasks();
    std::size_t sizeMask = (InfoComp::SIZE | InfoComp::COOLDOWNSHOOT | InfoComp::POS);
    Size size = {0, 0};
    CooldownShoot sizeProj = {0, 0};
    Position pos = {0, 0};
    bool enemy = masks[id].has_value() && (masks[id].value() & InfoComp::ENEMY) == InfoComp::ENEMY ? true : false;
    sf::Vector2f sizeFire = sf::Vector2f(56 / screenSize->x * windowsSize.x, 32 / screenSize->y * windowsSize.y);
    std::size_t addEntity = entityManager.addMask(
        (InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::PROJECTILE | InfoComp::SIZE | InfoComp::SPRITEAT),
        componentManager);

    if (masks[id].has_value() && (masks[id].value() & sizeMask) == sizeMask) {
        size = componentManager.getSingleComponent<Size>(id);
        sizeProj = componentManager.getSingleComponent<CooldownShoot>(id);
        pos = componentManager.getSingleComponent<Position>(id);
    }
    if (!enemy)
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((damage == 2) ? 4 : 3), Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 56, 0});
    else
        componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{9, Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 56, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(addEntity, SpriteAttribut{0, {0, 0, 56, 32}, sf::Color::White, {(sizeProj.size / screenSize->x * windowsSize.x), sizeProj.size / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x, (pos.y + (size.y / 2)) - (sizeFire.y * sizeProj.size / 2), pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{15 / screenSize->x * windowsSize.x * (enemy ? -1 : 1), 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, damage, sizeProj.size});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{sizeFire.x * sizeProj.size, sizeFire.y * sizeProj.size});
    addEntity = entityManager.addMask((InfoComp::SOUNDID), componentManager);
    if (!enemy) {
        float pitch = (sizeProj.size == 1) ? 1 : (1 - (sizeProj.size / 10)) < 0.2 ? 0.2
                                                                                  : (1 - (sizeProj.size / 10));
        componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, pitch});
    }
}

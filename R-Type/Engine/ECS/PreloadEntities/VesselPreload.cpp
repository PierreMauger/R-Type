#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

using namespace eng;

void VesselPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId)
{
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT), componentManager);
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    sf::Vector2f size{screenSize->x / (1920 / 2), screenSize->y / (1080 / 2)};

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, false, false, 0, 0, 64, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {size.x / screenSize->x * windowsSize.x, size.y / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, screenSize->x / (1920 / 10) / screenSize->x * windowsSize.x, screenSize->y / (1080 / 10) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(windowsSize.y + (100 / screenSize->y * windowsSize.y))});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{64 * size.x / screenSize->x * windowsSize.x, 28 * size.y / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{syncId++});

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR | InfoComp::SYNCID), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::LOW});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(graphic.getWindow()->getSize().y) - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
    componentManager.getComponent(typeid(SyncID)).emplaceData(idBar, SyncID{syncId++});
}

void VesselPreload::preloadScore(EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, std::size_t kill, std::size_t death, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize)
{
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT), componentManager);
    sf::Vector2f size{screenSize->x / (1920 / 2), screenSize->y / (1080 / 2)};

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, false, false, 0, 0, 64, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {size.x / screenSize->x * windowsSize.x, size.y / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, screenSize->x / (1920 / 10) / screenSize->x * windowsSize.x, screenSize->y / (1080 / 10) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(windowsSize.y + 100 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true, kill, death});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{64 * size.x / screenSize->x * windowsSize.x, 28 * size.y / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{syncId++});

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::LOW});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(windowsSize.y) - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
    componentManager.getComponent(typeid(SyncID)).emplaceData(idBar, SyncID{syncId++});
}

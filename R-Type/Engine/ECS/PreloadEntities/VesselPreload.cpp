#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

using namespace eng;

void VesselPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId)
{
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT), componentManager);
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    sf::Vector2f size{windowsSize.x / (screenSize->x / 2), windowsSize.y / (screenSize->y / 2)};

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_VESSEL, Priority::MEDIUM, 0, 0, false, false, 0, 0, 64, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {size.x, size.y}, {size.x / 2, size.y / 2}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, windowsSize.x / (screenSize->x / 10), windowsSize.y / (screenSize->y / 10)});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(windowsSize.y + (100 / screenSize->y * windowsSize.y))});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{64 * size.x, 28 * size.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{syncId++});

    std::size_t idShield = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::SHIELD | InfoComp::SYNCID), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(idShield, SpriteID{S_SHIELD, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(idShield, SpriteAttribut{0, {0, 0, 700, 440}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}, {700 / 2 - (64 * size.x) / 2, 440 / 2 - (28 * size.x) / 2}});
    componentManager.getComponent(typeid(Position)).emplaceData(idShield, Position{0, 0, 0});
    componentManager.getComponent(typeid(Shield)).emplaceData(idShield, Shield{5});
    componentManager.getComponent(typeid(SyncID)).emplaceData(idShield, SyncID{syncId++});
    componentManager.getComponent(typeid(Parent)).emplaceData(idShield, Parent{componentManager.getSingleComponent<SyncID>(id).id});

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR | InfoComp::SYNCID), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{S_IDBAR, Priority::LOW});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(graphic.getWindow()->getSize().y) - 20, 0});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
    componentManager.getComponent(typeid(SyncID)).emplaceData(idBar, SyncID{syncId++});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{componentManager.getSingleComponent<SyncID>(id).id});
}

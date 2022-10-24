#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

using namespace eng;

void VesselPreload::preload(Engine &engine)
{
    ComponentManager &componentManager = engine.getECS().getComponentManager();
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE |
                                                                 InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT),
                                                                componentManager);
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 64, 0});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5 / screenSize->x * windowsSize.x, 5 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    componentManager.getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(engine.getGraphic().getWindow()->getSize().y + 100)});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{64 / screenSize->x * windowsSize.x, 28 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{0});

    std::size_t idBar = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(engine.getGraphic().getWindow()->getSize().y) - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

void VesselPreload::preloadScore(Engine &engine, std::size_t kill, std::size_t death)
{
    ComponentManager &componentManager = engine.getECS().getComponentManager();
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE |
                                                                 InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT),
                                                                componentManager);
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 64, 0});
    engine.getECS()
        .getComponentManager()
        .getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5 / screenSize->x * windowsSize.x, 5 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    componentManager.getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(engine.getGraphic().getWindow()->getSize().y + 100)});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true, kill, death});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{64 / screenSize->x * windowsSize.x, 28 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{0});

    std::size_t idBar = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(engine.getGraphic().getWindow()->getSize().y) - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

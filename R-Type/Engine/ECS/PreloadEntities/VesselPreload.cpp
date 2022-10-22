#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

void eng::VesselPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE |
                                                                 InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT),
                                                                engine.getECS().getComponentManager());
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 64, 0});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {
        1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5 / screenSize->x * windowsSize.x, 5 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    engine.getECS().getComponentManager().getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(engine.getGraphic().getWindow()->getSize().y + 100)});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{64 / screenSize->x * windowsSize.x, 28 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{1});
    engine.getECS().getComponentManager().getComponent(typeid(SyncID)).emplaceData(id, SyncID{0});

    std::size_t idBar =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(engine.getGraphic().getWindow()->getSize().y) - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

void eng::VesselPreload::preloadScore(Engine &engine, std::size_t kill, std::size_t death)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE |
                                                                 InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::DIS | InfoComp::SYNCID | InfoComp::SPRITEAT),
                                                                engine.getECS().getComponentManager());
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 64, 0});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 64, 28}, sf::Color::White, {
        1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, 28 / screenSize->y * windowsSize.y * -1, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5 / screenSize->x * windowsSize.x, 5 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    engine.getECS().getComponentManager().getComponent(typeid(Disappearance)).emplaceData(id, Disappearance{false, static_cast<float>(engine.getGraphic().getWindow()->getSize().y + 100)});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(id, Controllable{true, kill, death});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{64 / screenSize->x * windowsSize.x, 28 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{1});
    engine.getECS().getComponentManager().getComponent(typeid(SyncID)).emplaceData(id, SyncID{0});

    std::size_t idBar =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(engine.getGraphic().getWindow()->getSize().y) - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}
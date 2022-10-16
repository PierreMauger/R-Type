#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

void eng::VesselPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP),
        engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 64, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, -200, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{64, 28});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{1});

    std::size_t idBar =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(engine.getGraphic().getWindow()->getSize().y) - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

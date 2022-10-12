#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

void eng::VesselPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::POS | eng::InfoEntity::LIFE | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID |
                                                                 eng::InfoEntity::CONTROLLABLE | eng::InfoEntity::COOLDOWNSHOOT | eng::InfoEntity::SIZE),
                                                                engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{100, 118});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{1});

    std::size_t idBar = engine.getECS().getEntityManager().addMask((eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT | eng::InfoEntity::COOLDOWNBAR),
                                                                   engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

#include "Engine/ECS/PreloadEntities/BossPreload.hpp"

void eng::BossPreload::preload(Engine &engine)
{
    std::size_t id =
        engine.getECS().getEntityManager().addMask((eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::APP | eng::InfoEntity::SPRITEID | eng::InfoEntity::ENEMY |
                                                    eng::InfoEntity::LIFE | eng::InfoEntity::SIZE | eng::InfoEntity::PATERN | eng::InfoEntity::DROP),
                                                   engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5, Priority::MEDIUM});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{430, -300, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, -2, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(3), 0, {430, 100 - 2}});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, 0.4});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{300, 259});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{25});
    engine.getECS().getComponentManager().getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{1});

    std::size_t idBar = engine.getECS().getEntityManager().addMask((eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT | eng::InfoEntity::LIFEBAR),
                                                                   engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(LifeBar)).emplaceData(idBar, LifeBar{true, 25});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::MEDIUM});
}

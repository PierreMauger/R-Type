#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"

void eng::EnemyPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATERN), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{2, Priority::MEDIUM, 0, 2, false, 0.4, 0, 63, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{800, 200, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, -2, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(1), 0, {800, 200}});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, (float)(1 == 0 ? 1.0 : 0.0)});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{63, 48});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{2});
}

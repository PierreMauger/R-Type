#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"

void eng::EnemyPreload::preload(Engine &engine)
{
    std::size_t rand = static_cast<std::size_t>(createRandom(0, 2));
    float randY = createRandom(150, 450);
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATERN), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{2, Priority::MEDIUM, 0, 2, false, 63, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{800, randY, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, -2, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(rand), 0, {800, randY}});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, (float)(rand == 0 ? 1.0 : 0.0)});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{63, 48});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{2});
}

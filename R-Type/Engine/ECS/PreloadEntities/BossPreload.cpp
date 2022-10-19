#include "Engine/ECS/PreloadEntities/BossPreload.hpp"

void eng::BossPreload::preload(Engine &engine)
{
    float randY = createRandom(180, 420);
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::VEL | InfoComp::APP | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE |
                                                                 InfoComp::SIZE | InfoComp::PATERN | InfoComp::DROP | InfoComp::SPRITEAT),
                                                                engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5, Priority::MEDIUM, 0, 4, false, 0, 0.2, 96, 0});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 96, 96}});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, randY});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(engine.getGraphic().getWindow()->getSize().x - 280), -300, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, -2, 0, 2});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern::CIRCLE, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, 0.4});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{96, 96});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{10});
    engine.getECS().getComponentManager().getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{1});

    std::size_t idBar =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::LIFEBAR), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(LifeBar)).emplaceData(idBar, LifeBar{true, 10});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::MEDIUM});
}

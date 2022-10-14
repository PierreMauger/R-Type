#include "Engine/ECS/PreloadEntities/BossPreload.hpp"

void eng::BossPreload::preload(Engine &engine, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::APP | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATERN | InfoComp::DROP),
        engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5, Priority::MEDIUM, 0, 4, false, 0.3, 0, 48, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{430, -300, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, -2, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(3), 0, {430, 100 - 2}});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, 0.4});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{48, 48});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{25});
    engine.getECS().getComponentManager().getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{1});
    sprites->at(5).setTextureRect(sf::IntRect(0, 0, 48, 48));

    std::size_t idBar =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::LIFEBAR), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(LifeBar)).emplaceData(idBar, LifeBar{true, 25});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::MEDIUM});
}

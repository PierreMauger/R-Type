#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"

void eng::ParallaxPreload::preload(Engine &engine, [[maybe_unused]] std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{7, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{11, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{8, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{10, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 250, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{9, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
}

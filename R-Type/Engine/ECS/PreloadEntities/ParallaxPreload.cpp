#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"

void eng::ParallaxPreload::preload(EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = entityManager.addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{3});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{3});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{800, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{4});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{400, 250, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{7});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{800, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
}

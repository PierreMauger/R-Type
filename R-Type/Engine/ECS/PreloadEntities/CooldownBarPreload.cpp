#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"

void eng::CooldownBarPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT | eng::InfoEntity::COOLDOWNBAR),
                                                                engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{1, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(id, Parent{5});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(id, CooldownBar{true});
}

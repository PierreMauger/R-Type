#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"

void eng::VesselPreload::preload(Engine &engine)
{
    this->_id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE |
                                                                 InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP | InfoComp::SYNCID),
                                                                engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(this->_id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 64, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(this->_id, Position{10, -200, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(this->_id, Velocity{0, 0, 0, 5});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(this->_id, Appearance{true, 100});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(this->_id, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(this->_id, CooldownShoot{0, 1, 1});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(this->_id, Size{64, 28});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(this->_id, Life{1});
    engine.getECS().getComponentManager().getComponent(typeid(SyncID)).emplaceData(this->_id, SyncID{0});

    std::size_t idBar =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(engine.getGraphic().getWindow()->getSize().y) - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{this->_id});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

void eng::VesselPreload::setSyncId(Engine &engine, size_t syncId)
{
    engine.getECS().getComponentManager().getComponent(typeid(SyncID)).emplaceData(this->_id, SyncID{syncId});
}

size_t eng::VesselPreload::getSyncId()
{
    return this->_syncId;
}
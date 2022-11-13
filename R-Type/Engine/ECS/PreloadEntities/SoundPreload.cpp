#include "Engine/ECS/PreloadEntities/SoundPreload.hpp"

using namespace eng;

void SoundPreload::preload(EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, SoundID sound)
{
    std::size_t id = entityManager.addMask((InfoComp::SOUNDID | InfoComp::SYNCID), componentManager);

    componentManager.getComponent(typeid(SoundID)).emplaceData(id, sound);
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{*syncId});
    *syncId += 1;
}

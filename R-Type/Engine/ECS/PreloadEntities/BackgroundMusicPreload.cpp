#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"

using namespace eng;

void BackgroundMusicPreload::preload([[maybe_unused]] Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = entityManager.addMask((InfoComp::SOUNDID), componentManager);

    componentManager.getComponent(typeid(SoundID)).emplaceData(id, SoundID{1, false, true});
}

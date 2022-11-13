#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"

using namespace eng;

void BackgroundMusicPreload::preload([[maybe_unused]] Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = entityManager.addMask((InfoComp::SOUNDID), componentManager);

    componentManager.getComponent(typeid(SoundID)).emplaceData(id, SoundID{A_MUSIC, false, true});
}

void BackgroundMusicPreload::preloadMusic(EntityManager &entityManager, ComponentManager &componentManager, std::size_t idSound)
{
    std::size_t id = entityManager.addMask((InfoComp::SOUNDID), componentManager);

    componentManager.getComponent(typeid(SoundID)).emplaceData(id, SoundID{idSound, false, false});
}

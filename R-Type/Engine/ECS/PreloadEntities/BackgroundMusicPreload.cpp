#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"

using namespace eng;

void BackgroundMusicPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::SOUNDID), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SoundID)).emplaceData(id, SoundID{1, false, true});
}

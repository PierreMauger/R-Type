#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"

using namespace eng;

void ScoreTextPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t idScore = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idScore, Text{"Score: ", true, 0, {static_cast<float>(graphic.getWindow()->getSize().x - 100), 10}});

    std::size_t idKill = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idKill, Text{"Death: ", true, 0, {static_cast<float>(graphic.getWindow()->getSize().x - 100), 50}});
}

#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"

void eng::ScoreTextPreload::preload(Engine &engine)
{
    std::size_t idScore =
        engine.getECS().getEntityManager().addMask((InfoComp::TEXT), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(Text)).emplaceData(idScore, Text{"Score: ", 0, {static_cast<float>(engine.getGraphic().getWindow()->getSize().x - 100), 10}});

    std::size_t idKill =
        engine.getECS().getEntityManager().addMask((InfoComp::TEXT), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(Text)).emplaceData(idKill, Text{"Death: ", 0, {static_cast<float>(engine.getGraphic().getWindow()->getSize().x - 100), 50}});
}
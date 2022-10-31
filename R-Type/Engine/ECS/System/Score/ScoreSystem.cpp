#include "Engine/ECS/System/Score/ScoreSystem.hpp"

using namespace eng;

ScoreSystem::ScoreSystem()
{
}

bool ScoreSystem::findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &controllable)
{
    std::size_t checkCon = (InfoComp::CONTROLLABLE);

    for (auto id : entityManager.getMaskCategory(checkCon)) {
        controllable = componentManager.getSingleComponent<Controllable>(id);
        return true;
    }
    return false;
}

void ScoreSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t checkText = (InfoComp::TEXT);
    Controllable controllable;

    findVessel(componentManager, entityManager, controllable);
    for (auto id : entityManager.getMaskCategory(checkText)) {
        Text &txt = componentManager.getSingleComponent<Text>(id);
        if (txt.str == "Death: ")
            txt.value = controllable.death;
        if (txt.str == "Score: ")
            txt.value = controllable.kill;
    }
}

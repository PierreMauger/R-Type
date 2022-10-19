#include "Engine/ECS/System/Score/ScoreSystem.hpp"

using namespace eng;

ScoreSystem::ScoreSystem()
{

}

bool ScoreSystem::findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &controllable)
{
    auto &masks = entityManager.getMasks();
    std::size_t checkCon = (InfoComp::CONTROLLABLE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkCon) == checkCon) {
            controllable = componentManager.getSingleComponent<Controllable>(i);
            return true;
        }
    }
    return false;
}

void ScoreSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t checkText = (InfoComp::TEXT);
    Controllable controllable;

    findVessel(componentManager, entityManager, controllable);
    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkText) == checkText) {
            Text &txt = componentManager.getSingleComponent<Text>(i);
            if (txt.str == "Death: ")
                txt.value = controllable.death;
            if (txt.str == "Score: ")
                txt.value = controllable.kill;
        }
    }
}
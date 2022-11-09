#include "Engine/ECS/System/Score/ScoreSystem.hpp"

using namespace eng;

ScoreSystem::ScoreSystem(EntityManager &entityManager)
{
    entityManager.addMaskCategory(this->_textTag);
    entityManager.addMaskCategory(this->_controlTag);
}

bool ScoreSystem::findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &controllable)
{
    for (auto id : entityManager.getMaskCategory(this->_controlTag)) {
        controllable = componentManager.getSingleComponent<Controllable>(id);
        return true;
    }
    return false;
}

void ScoreSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Controllable controllable;

    findVessel(componentManager, entityManager, controllable);
    for (auto id : entityManager.getMaskCategory(this->_textTag)) {
        Text &txt = componentManager.getSingleComponent<Text>(id);
        if (txt.str == "Death: ")
            txt.value = controllable.death;
        if (txt.str == "Score: ")
            txt.value = controllable.kill;
    }
}

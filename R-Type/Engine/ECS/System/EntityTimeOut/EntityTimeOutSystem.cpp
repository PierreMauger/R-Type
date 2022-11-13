#include "Engine/ECS/System/EntityTimeOut/EntityTimeOutSystem.hpp"

using namespace eng;

EntityTimeOutSystem::EntityTimeOutSystem(Graphic &graphic, EntityManager &entityManager)
{
    this->_clock = graphic.getClock();

    entityManager.addMaskCategory(InfoComp::SYNCID);
}

void EntityTimeOutSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &arraySyncId = entityManager.getMaskCategory(InfoComp::SYNCID);

    for (std::size_t i = 0; i < arraySyncId.size(); i++) {
        auto &syncId = componentManager.getSingleComponent<SyncID>(arraySyncId[i]);
        if (syncId.lastRefresh > this->_clock->getElapsedTime().asMilliseconds()) {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
            i--;
        }
    }
}

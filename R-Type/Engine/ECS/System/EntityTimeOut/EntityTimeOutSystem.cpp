#include "Engine/ECS/System/EntityTimeOut/EntityTimeOutSystem.hpp"

using namespace eng;

EntityTimeOutSystem::EntityTimeOutSystem(Graphic &graphic, [[maybe_unused]] EntityManager &entityManager)
{
    this->_clock = graphic.getClock();
    this->_isLocal = graphic.getIsLocal();
}

void EntityTimeOutSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    if (*this->_isLocal)
        return;

    auto &masks = entityManager.getMasks();

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || (masks[i].value() & InfoComp::SYNCID) != InfoComp::SYNCID) {
            continue;
        }
        auto &syncId = componentManager.getSingleComponent<SyncID>(i);
        if (syncId.lastRefresh < this->_clock->getElapsedTime().asSeconds()) {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
        }
    }
}

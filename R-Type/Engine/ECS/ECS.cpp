#include "Engine/ECS/ECS.hpp"

using namespace eng;

ECS::ECS()
{
    this->_entityManager = EntityManager();
    this->_componentManager = ComponentManager();
    this->_systemManager = SystemManager();
}

void ECS::update()
{
    this->_systemManager.updateSystems(this->_componentManager, this->_entityManager);
}

EntityManager &ECS::getEntityManager()
{
    return this->_entityManager;
}

ComponentManager &ECS::getComponentManager()
{
    return this->_componentManager;
}

SystemManager &ECS::getSystemManager()
{
    return this->_systemManager;
}

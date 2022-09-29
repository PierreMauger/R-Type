#include "Engine.hpp"

using namespace ECS;

Engine::Engine()
{
    this->_entityManager = EntityManager();
    this->_componentManager = ComponentManager();
    this->_systemManager = SystemManager();
}

void Engine::run()
{
    while (1)
        this->_systemManager.updateSystems(this->_componentManager);
}

EntityManager &Engine::getEntityManager()
{
    return this->_entityManager;
}

ComponentManager &Engine::getComponentManager()
{
    return this->_componentManager;
}

SystemManager &Engine::getSystemManager()
{
    return this->_systemManager;
}

#include "System/SystemManager.hpp"

using namespace ECS;

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
    for (auto &system : this->_systems)
        system.reset();
}

std::vector<std::shared_ptr<ISystem>> &SystemManager::getSystems()
{
    return this->_systems;
}

void SystemManager::addSystem(std::shared_ptr<ISystem> system)
{
    this->_systems.push_back(system);
}

void SystemManager::updateSystems(ComponentManager &componentManager)
{
    for (auto &system : this->_systems)
        system->update(componentManager);
}

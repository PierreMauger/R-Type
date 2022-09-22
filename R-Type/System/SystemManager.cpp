#include "SystemManager.hpp"

using namespace ECS;

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
    for (auto &system : this->_systems)
        system.reset();
}

std::vector<std::unique_ptr<ASystem>> &SystemManager::getSystems()
{
    return this->_systems;
}

void SystemManager::addSystem(std::unique_ptr<ASystem> system)
{
    this->_systems.push_back(std::move(system));
}

void SystemManager::updateSystems(ComponentManager componentManager)
{
    for (auto &system : this->_systems)
        system->update(componentManager);
}

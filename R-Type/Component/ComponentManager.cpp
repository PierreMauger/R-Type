#include "Component/ComponentManager.hpp"

using namespace ECS;

ComponentManager::ComponentManager()
{
}

std::map<std::type_index, std::vector<std::optional<std::any>>> &ComponentManager::getComponentArray()
{
    return this->_componentArray;
}

std::vector<std::optional<std::any>> &ComponentManager::getComponent(std::type_index type)
{
    if (this->_componentArray.find(type) == this->_componentArray.end())
        throw std::runtime_error("Component not found");
    return this->_componentArray[type];
}

void ComponentManager::addComponent(std::type_index type, std::vector<std::optional<std::any>> component)
{
    this->_componentArray[type] = component;
}

void ComponentManager::addSpecificComponent(std::type_index type, std::size_t id, std::any component)
{
    auto it = this->_componentArray.begin();

    for (; it != this->_componentArray.end(); ++it)
        if (it->first == type)
            break;
    if (it == this->_componentArray.end())
        throw std::runtime_error("Component not found");
    if (id >= it->second.size())
        it->second.push_back(component);
    else
        it->second.at(id) = component;
}

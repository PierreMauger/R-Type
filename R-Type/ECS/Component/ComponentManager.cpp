#include "ECS/Component/ComponentManager.hpp"

using namespace ECS;

ComponentManager::ComponentManager()
{
}

std::map<std::type_index, Component> &ComponentManager::getComponentArray()
{
    return this->_componentArray;
}

Component &ComponentManager::getComponent(std::type_index type)
{
    if (this->_componentArray.find(type) == this->_componentArray.end())
        throw std::runtime_error("Component not found");
    return this->_componentArray[type];
}

void ComponentManager::addComponent(std::type_index type, Component component)
{
    this->_componentArray[type] = component;
}

void ComponentManager::initEmptyComponent()
{
    for (auto &component : this->_componentArray)
        component.second.addEmptyField();
}

void ComponentManager::killEntity(std::size_t id)
{
    for (auto &component : this->_componentArray)
        component.second.destroyData(id);
}

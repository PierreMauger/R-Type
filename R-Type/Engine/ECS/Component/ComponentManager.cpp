#include "Engine/ECS/Component/ComponentManager.hpp"

using namespace eng;

ComponentManager::ComponentManager()
{
}

std::map<std::type_index, SparseArray> &ComponentManager::getComponentArray()
{
    return this->_componentArray;
}

SparseArray &ComponentManager::getComponent(std::type_index type)
{
    if (this->_componentArray.find(type) == this->_componentArray.end())
        throw std::runtime_error("Component not found");
    return this->_componentArray[type];
}

SparseArray &ComponentManager::getComponent(std::size_t index)
{
    if (index >= this->_componentArray.size())
        throw std::runtime_error("Component not found");
    return this->_componentArray[this->_orderedMap.at(index)];
}

std::type_index ComponentManager::getComponentType(std::size_t index)
{
    if (index >= this->_componentArray.size())
        throw std::runtime_error("Component not found");
    return this->_orderedMap.at(index);
}

void ComponentManager::initNewComponent(std::size_t id)
{
    for (auto &[index, component] : this->_componentArray)
        component.addData(id, std::nullopt);
}

void ComponentManager::addEntity(std::size_t id)
{
    for (auto &[type, component] : this->_componentArray)
        component.addData(id, std::nullopt);
}

void ComponentManager::removeSingleComponent(std::size_t id, std::type_index type)
{
    if (this->_componentArray.find(type) == this->_componentArray.end())
        throw std::runtime_error("Component not found");
    this->_componentArray[type].destroyData(id);
}

void ComponentManager::removeAllComponents(std::size_t id)
{
    for (auto &[type, component] : this->_componentArray)
        component.destroyData(id);
}

void ComponentManager::updateComponent(std::size_t id)
{
    for (auto &[type, component] : this->_componentArray)
        component.emplaceData(id, std::nullopt);
}

void ComponentManager::clear()
{
    for (auto &[type, component] : this->_componentArray)
        component.clear();
}

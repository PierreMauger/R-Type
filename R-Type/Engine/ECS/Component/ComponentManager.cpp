#include "Engine/ECS/Component/ComponentManager.hpp"

using namespace eng;

ComponentManager::ComponentManager()
{
}

std::vector<std::pair<std::type_index, Component>> &ComponentManager::getComponentArray()
{
    return this->_componentArray;
}

Component &ComponentManager::getComponent(std::type_index type)
{
    for (auto &[index, component] : this->_componentArray) {
        if (index == type)
            return component;
    }
    throw std::runtime_error("Component not found");
}

void ComponentManager::addComponent(std::type_index type, Component component)
{
    this->_componentArray.push_back(std::make_pair(type, component));
}

void ComponentManager::initEmptyComponent()
{
    for (auto &[index, component] : this->_componentArray)
        component.addEmptyField();
}

void ComponentManager::destroyComponent(std::size_t id, std::type_index type)
{
    for (auto &[index, component] : this->_componentArray) {
        if (index == type) {
            component.destroyData(id);
            return;
        }
    }
    throw std::runtime_error("Component not found");
}

void ComponentManager::killEntity(std::size_t id)
{
    for (auto &[index, component] : this->_componentArray)
        component.destroyData(id);
}

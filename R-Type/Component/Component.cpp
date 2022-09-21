#include "Component.hpp"

Component::Component()
{
}

std::map<std::type_index, std::vector<std::optional<std::any>>> &Component::getComponentArray()
{
    return this->_componentArray;
}

std::vector<std::optional<std::any>> &Component::getComponent(std::type_index type)
{
    if (this->_componentArray.find(typeid(type)) == this->_componentArray.end())
        throw std::runtime_error("Component not found");
    return this->_componentArray[typeid(type)];
}

void Component::addComponent(std::type_index type, std::vector<std::optional<std::any>> component)
{
    this->_componentArray[type] = component;
}

#include "Component/Component.hpp"

using namespace ECS;

Component::Component()
{
}

void Component::addEmptyField()
{
    this->_component.push_back({});
}

void Component::emplaceData(std::size_t id, std::any data)
{
    if (id > this->_component.size())
        throw std::runtime_error("incorrect ID");
    this->_component[id] = data;
}

std::optional<std::any> &Component::getField(std::size_t id)
{
    if (id > this->_component.size())
        throw std::runtime_error("incorrect ID");
    return this->_component[id];
}

std::size_t Component::getSize()
{
    return this->_component.size();
}

#include "Entity.hpp"

Entity::Entity()
{
}

std::vector<std::optional<size_t>> &Entity::getMasks()
{
    return this->_masks;
}

void Entity::addMask(size_t id, std::optional<size_t> mask)
{
    if (this->_masks.size() <= id)
        this->_masks.resize(id + 1);
    this->_masks[id] = mask;
}

void Entity::removeMask(size_t id)
{
    if (this->_masks.size() <= id)
        return;
    this->_masks[id] = std::nullopt;
}

void Entity::updateMask(size_t id, std::optional<size_t> mask)
{
    if (this->_masks.size() <= id)
        return;
    this->_masks[id] = mask;
}

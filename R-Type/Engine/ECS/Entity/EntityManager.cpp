#include "Engine/ECS/Entity/EntityManager.hpp"

using namespace eng;

EntityManager::EntityManager()
{
}

std::vector<std::optional<std::size_t>> &EntityManager::getMasks()
{
    return this->_masks;
}

void EntityManager::addMaskCategory(std::size_t category)
{
    this->_maskCategory[category] = std::vector<std::size_t>();
}

std::vector<std::size_t> &EntityManager::getMaskCategory(std::size_t category)
{
    return this->_maskCategory[category];
}

std::size_t EntityManager::addMask(std::optional<std::size_t> mask, ComponentManager &componentManager)
{
    for (std::size_t i = 0; i < this->_masks.size(); i++) {
        if (!this->_masks[i].has_value()) {
            this->_masks[i] = mask;
            for (auto &[key, value] : this->_maskCategory)
                if (mask.has_value() && (mask.value() & key) == key)
                    value.push_back(i);
            return i;
        }
    }
    this->_masks.push_back(mask);
    componentManager.initNewComponent(this->_masks.size() - 1);
    for (auto &[key, value] : this->_maskCategory)
        if (mask.has_value() && (mask.value() & key) == key)
            value.push_back(this->_masks.size() - 1);

    return (this->_masks.size() - 1);
}

void EntityManager::removeMask(std::size_t id)
{
    if (this->_masks.size() <= id)
        return;
    this->_masks[id] = std::nullopt;

    for (auto &[key, value] : this->_maskCategory)
        value.erase(std::remove(value.begin(), value.end(), id), value.end());
}

void EntityManager::updateMask(std::size_t id, std::optional<std::size_t> mask)
{
    if (this->_masks.size() <= id)
        return;
    this->_masks[id] = mask;

    for (auto &[key, value] : this->_maskCategory) {
        value.erase(std::remove(value.begin(), value.end(), id), value.end());
        if (mask.has_value() && (mask.value() & key) == key)
            value.push_back(id);
    }
}

void EntityManager::clear()
{
    this->_masks.clear();
}

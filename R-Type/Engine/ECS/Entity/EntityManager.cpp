#include "Engine/ECS/Entity/EntityManager.hpp"

using namespace eng;

EntityManager::EntityManager()
{
}

std::vector<std::optional<std::size_t>> &EntityManager::getMasks()
{
    return this->_masks;
}

std::size_t EntityManager::addMask(std::optional<std::size_t> mask, ComponentManager &componentManager)
{
    for (std::size_t i = 0; i < this->_masks.size(); i++) {
        if (!this->_masks[i].has_value()) {
            this->_masks[i] = mask;
            return i;
        }
    }
    this->_masks.push_back(mask);
    componentManager.initNewComponent();
    return (this->_masks.size() - 1);
}

void EntityManager::removeMask(std::size_t id)
{
    if (this->_masks.size() <= id)
        return;
    this->_masks[id] = std::nullopt;
}

void EntityManager::updateMask(std::size_t id, std::optional<std::size_t> mask)
{
    if (this->_masks.size() <= id)
        return;
    this->_masks[id] = mask;
}

// void EntityManager::readMask(std::size_t id, ComponentManager &componentManager)
//{
//  auto it = componentManager.getComponentArray().begin();

// for (unsigned short i = 0; i < 32; i++) {
//     if (std::bitset<sizeof(std::size_t)>(this->_masks[id].value()).test(i))
//         it->second.emplaceData({0});
//     else
//         it->second.emplaceData(std::nullopt);
//     it++;
// }
//}

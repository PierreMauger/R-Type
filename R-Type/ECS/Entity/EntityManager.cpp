#include "ECS/Entity/EntityManager.hpp"

using namespace ECS;

EntityManager::EntityManager()
{
}

std::vector<std::optional<std::size_t>> &EntityManager::getMasks()
{
    return this->_masks;
}

void EntityManager::addMask(std::size_t id, std::optional<std::size_t> mask)
{
    if (this->_masks.size() <= id)
        this->_masks.resize(id + 1);
    this->_masks[id] = mask;
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

//void EntityManager::readMask(std::size_t id, ComponentManager &componentManager)
//{
    // auto it = componentManager.getComponentArray().begin();

    // for (unsigned short i = 0; i < 32; i++) {
    //     if (std::bitset<sizeof(std::size_t)>(this->_masks[id].value()).test(i))
    //         it->second.emplaceData({0});
    //     else
    //         it->second.emplaceData(std::nullopt);
    //     it++;
    // }
//}

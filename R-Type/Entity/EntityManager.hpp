#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Includes.hpp"

namespace ECS
{
    class EntityManager
    {
        private:
            std::vector<std::optional<std::size_t>> _masks;

        public:
            EntityManager();
            ~EntityManager() = default;

            std::vector<std::optional<std::size_t>> &getMasks();
            void addMask(std::size_t id, std::optional<std::size_t> mask, ComponentManager &componentManager);
            void removeMask(std::size_t id);
            void updateMask(std::size_t id, std::optional<std::size_t> mask);
            void readMask(std::size_t id, ComponentManager &componentManager);
    };
}

#endif // ENTITYMANAGER_HPP
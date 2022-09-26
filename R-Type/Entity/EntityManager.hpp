#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Component/ComponentManager.hpp"

namespace ECS
{
    enum InfoEntity {
        POS = 0b100000000000000000000000000000000000000000000000000000000000000,
        VEL = 0b010000000000000000000000000000000000000000000000000000000000000,
        IDMODEL = 0b001000000000000000000000000000000000000000000000000000000000000
    };

    class EntityManager

    {
        private:
            std::vector<std::optional<std::size_t>> _masks;

        public:
            EntityManager();
            ~EntityManager() = default;

            std::vector<std::optional<std::size_t>> &getMasks();
            void addMask(std::size_t id, std::optional<std::size_t> mask);
            void removeMask(std::size_t id);
            void updateMask(std::size_t id, std::optional<std::size_t> mask);
            void readMask(std::size_t id, ComponentManager &componentManager);
    };
}

#endif // ENTITYMANAGER_HPP

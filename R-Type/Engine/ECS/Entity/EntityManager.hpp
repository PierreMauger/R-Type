#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"

namespace eng
{
    enum InfoEntity {
        POS = 0b1,
        VEL = 0b10,
        IDMODEL = 0b100,
        SPEED = 0b1000,
        CONTROLLABLE = 0b10000,
        PARALLAX = 0b100000,
        PARENT = 0b1000000,
        COOLDOWNSHOOT = 0b10000000,
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
            // void readMask(std::size_t id, ComponentManager &componentManager);
    };
}

#endif // ENTITYMANAGER_HPP

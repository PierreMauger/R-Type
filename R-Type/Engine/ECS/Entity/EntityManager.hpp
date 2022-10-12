#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"

namespace eng
{
    enum InfoEntity {
        POS = 0b1,
        VEL = 0b10,
        SIZE = 0b100,
        SPRITEID = 0b1000,
        CONTROLLABLE = 0b10000,
        PARALLAX = 0b100000,
        PROJECTILE = 0b1000000,
        LIFE = 0b10000000,
        ENEMY = 0b100000000,
        APP = 0b1000000000,
        SPEED = 0b10000000000,
        COOLDOWNSHOOT = 0b100000000000,
        COOLDOWNBAR = 0b1000000000000,
        LIFEBAR = 0b10000000000000,
        PARENT = 0b100000000000000,
        PATERN = 0b1000000000000000,
        SYNCID = 0b10000000000000000,
    };

    class EntityManager

    {
        private:
            std::vector<std::optional<std::size_t>> _masks;

        public:
            EntityManager();
            ~EntityManager() = default;

            std::vector<std::optional<std::size_t>> &getMasks();
            std::size_t addMask(std::optional<std::size_t> mask, ComponentManager &componentManager);
            void addManualMask(std::size_t id, std::optional<std::size_t> mask, ComponentManager &componentManager);
            void removeMask(std::size_t id);
            void updateMask(std::size_t id, std::optional<std::size_t> mask);
    };
}

#endif // ENTITYMANAGER_HPP

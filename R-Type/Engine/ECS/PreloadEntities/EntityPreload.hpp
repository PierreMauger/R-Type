#ifndef ENTITYPRELOAD_HPP
#define ENTITYPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"

namespace eng
{
    class EntityPreload
    {
        public:
            virtual ~EntityPreload() = default;

            virtual void preload(EntityManager &entityManager, ComponentManager &ComponentManager) = 0;
    };
}

#endif // ENTITYPRELOAD_HPP

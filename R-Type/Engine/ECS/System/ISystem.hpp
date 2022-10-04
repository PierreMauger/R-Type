#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Includes.hpp"

namespace eng
{
    class ISystem
    {
        public:
            virtual ~ISystem() = default;
            virtual void update(ComponentManager &componentManager, EntityManager &entityManager) = 0;
    };
}

#endif // ISYSTEM_HPP

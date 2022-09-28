#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

#include "ECS/Component/ComponentManager.hpp"
#include "Includes.hpp"

namespace ECS
{
    class ISystem
    {
        public:
            virtual ~ISystem() = default;
            virtual void update(ComponentManager &componentManager) = 0;
    };
}

#endif // ISYSTEM_HPP

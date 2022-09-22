#ifndef ASYSTEM_HPP
#define ASYSTEM_HPP

#include "ComponentManager.hpp"
#include "Includes.hpp"

namespace ECS
{
    class ASystem
    {
        public:
            virtual ~ASystem() = default;
            virtual void update(ComponentManager componentManager) = 0;
    };
}

#endif // ASYSTEM_HPP
#ifndef ENTITYPRELOAD_HPP
#define ENTITYPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/Engine.hpp"

namespace eng
{
    class EntityPreload
    {
        public:
            virtual ~EntityPreload() = default;

            virtual void preload(Engine &engine) = 0;
    };
}

#endif // ENTITYPRELOAD_HPP

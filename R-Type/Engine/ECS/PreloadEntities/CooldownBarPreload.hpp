#ifndef COOLDOWNBARPRELOAD_HPP
#define COOLDOWNBARPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class CooldownBarPreload : public EntityPreload
    {
        public:
            static void preload(Engine &engine);
    };
}

#endif // COOLDOWNBARPRELOAD_HPP

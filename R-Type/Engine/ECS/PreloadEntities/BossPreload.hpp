#ifndef BOSSPRELOAD_HPP
#define BOSSPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class BossPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine) override;
    };
}

#endif // BOSSPRELOAD_HPP

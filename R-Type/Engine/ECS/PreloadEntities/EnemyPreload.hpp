#ifndef ENEMYPRELOAD_HPP
#define ENEMYPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class EnemyPreload : public EntityPreload
    {
        public:
            static void preload(Engine &engine);
    };
}

#endif // ENEMYPRELOAD_HPP

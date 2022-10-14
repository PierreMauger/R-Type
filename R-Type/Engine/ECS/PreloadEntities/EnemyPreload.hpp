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
            void preload(Engine &engine, std::shared_ptr<std::vector<sf::Sprite>> sprites) override;
    };
}

#endif // ENEMYPRELOAD_HPP

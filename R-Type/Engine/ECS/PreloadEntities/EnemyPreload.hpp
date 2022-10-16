/**
 * @file EntityPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload an entity (parent class of the other preloads).
 * @copyright Epitech Rennes 2022
 */

#ifndef ENEMYPRELOAD_HPP
#define ENEMYPRELOAD_HPP

/// @cond
#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Preloads an entity.
     * @class EntityPreload
     */
    class EnemyPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the enemy.
             * @fn void preload(Engine &engine) override
             * @param engine A reference to the engine.
            */
            void preload(Engine &engine) override;
    };
}

#endif // ENEMYPRELOAD_HPP

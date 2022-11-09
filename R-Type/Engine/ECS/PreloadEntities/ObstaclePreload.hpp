/**
 * @file ObstaclePreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the enemy.
 * @copyright Epitech Rennes 2022
 */

#ifndef OBSTACLEPRELOAD_HPP
#define OBSTACLEPRELOAD_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Preloads the enemy.
     * @class ObstaclePreload
     */
    class ObstaclePreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the enemy.
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f pos)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f pos);
    };
}

#endif // OBSTACLEPRELOAD_HPP
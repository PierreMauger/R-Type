/**
 * @file BossPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the boss.
 * @copyright Epitech Rennes 2022
 */

#ifndef BOSSPRELOAD_HPP
#define BOSSPRELOAD_HPP

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
     * @brief Preloads the boss.
     * @class BossPreload
     */
    class BossPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the boss.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f position)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param syncId A reference to the synchronized id.
             * @param position The obstacle position.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f position);
    };
}

#endif // BOSSPRELOAD_HPP

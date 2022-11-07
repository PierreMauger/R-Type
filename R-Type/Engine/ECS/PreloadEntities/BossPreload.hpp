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
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2f pos);
    };
}

#endif // BOSSPRELOAD_HPP

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
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override
             * @param engine A reference to the engine.
            */
            void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override;
    };
}

#endif // BOSSPRELOAD_HPP

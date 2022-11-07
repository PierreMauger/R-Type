/**
 * @file CthulhuPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the Eye of Cthulhu (terraria boss).
 * @copyright Epitech Rennes 2022
 */

#ifndef CTHULHUPRELOAD_HPP_
#define CTHULHUPRELOAD_HPP_

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
     * @brief Preloads the Eye of Cthulhu.
     * @class CthulhuPreload
     */
    class CthulhuPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the Eye of Cthulhu.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2f pos);
    };
}

#endif /* !CTHULHUPRELOAD_HPP_ */
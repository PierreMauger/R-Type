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
             * @brief Preloads the cthulu.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f pos)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param syncId A reference to the synchronized id.
             * @param pos The obstacle position.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f pos);
    };
}

#endif /* !CTHULHUPRELOAD_HPP_ */

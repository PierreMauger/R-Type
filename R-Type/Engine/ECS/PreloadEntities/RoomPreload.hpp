/**
 * @file RoomPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the room.
 * @copyright Epitech Rennes 2022
 */

#ifndef ROOMPRELOAD_HPP
#define ROOMPRELOAD_HPP

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
     * @brief Preloads the room.
     * @class RoomPreload
     */
    class RoomPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the room.
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // ROOMPRELOAD_HPP

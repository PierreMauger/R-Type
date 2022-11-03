/**
 * @file MenuPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the menu.
 * @copyright Epitech Rennes 2022
 */

#ifndef MENUPRELOAD_HPP
#define MENUPRELOAD_HPP

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
     * @brief Preloads the menu.
     * @class MenuPreload
     */
    class MenuPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the menu.
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // MENUPRELOAD_HPP

/**
 * @file VesselPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the vessel (player).
 * @copyright Epitech Rennes 2022
 */

#ifndef VESSELPRELOAD_HPP
#define VESSELPRELOAD_HPP

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
     * @brief Preloads the vessel.
     * @class VesselPreload
     */
    class VesselPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the vessel.
             * @fn VesselPreload
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, SyncID syncId = {0});
            /**
             * @brief Preloads the vessel's (player's score)
             * @fn static void preloadScore(EntityManager &entityManager, ComponentManager &componentManager, std::size_t kill, std::size_t death, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize)
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param kill The player's kill count.
             * @param death The player's death count.
             * @param windowsSize The size of the window.
             * @param screenSize The size of the screen.
             */
            static void preloadScore(EntityManager &entityManager, ComponentManager &componentManager, std::size_t kill, std::size_t death, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize);
    };
}

#endif // VESSELPRELOAD_HPP

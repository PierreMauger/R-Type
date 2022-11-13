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
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param syncId The synchronized id of the vessel.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId);
            /**
             * @brief Preloads the vessel.
             * @fn void preload(sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId)
             * @param windowsSize The size of the window.
             * @param screenSize The size of the screen.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param syncId A reference to the synchronized id of the vessel.
             */
            static std::size_t preload(sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, std::size_t colorNum);
    };
}

#endif // VESSELPRELOAD_HPP

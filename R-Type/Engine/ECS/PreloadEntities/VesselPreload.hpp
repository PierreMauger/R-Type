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
            static std::size_t preload(sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, std::size_t colorNum);
    };
}

#endif // VESSELPRELOAD_HPP

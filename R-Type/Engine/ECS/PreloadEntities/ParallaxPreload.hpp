/**
 * @file ParallaxPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the parallax.
 * @copyright Epitech Rennes 2022
*/

#ifndef PARALLAXPRELOAD_HPP
#define PARALLAXPRELOAD_HPP

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
     * @brief Preloads the parallax.
     * @class ParallaxPreload
    */
    class ParallaxPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the parallax.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override
             * @param engine A reference to the engine.
            */
            void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override;
    };
}

#endif // PARALLAXPRELOAD_HPP

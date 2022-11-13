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
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
            /**
             * @brief Preloads the parallax.
             * @fn void preload(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize, EntityManager &entityManager, ComponentManager &componentManager)
             * @param window A shared pointer to the render window
             * @param screenSize A shared pointer to the screen size
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             */
            static void preload(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // PARALLAXPRELOAD_HPP

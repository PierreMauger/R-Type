/**
 * @file ProjectilePreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the projectile.
 * @copyright Epitech Rennes 2022
*/

#ifndef PROJECTILEPRELOAD_HPP
#define PROJECTILEPRELOAD_HPP

/// @cond
#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief Preloads the projectile.
     * @class ProjectilePreload
    */
    class ProjectilePreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the projectile.
             * @fn void preload(Engine &engine) override
             * @param engine A reference to the engine.
            */
            void preload(Engine &engine);
            /**
             * @brief Creates a shot
             * @fn static void createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, std::size_t id, std::size_t damage)
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param windowsSize The size of the window.
             * @param screenSize The size of the screen.
             * @param id The id of the projectile.
             * @param damage The damage of the projectile.
            */
            static void createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize,
                                    std::shared_ptr<sf::Vector2f> screenSize, std::size_t id, std::size_t damage);
    };
}

#endif // PROJECTILEPRELOAD_HPP

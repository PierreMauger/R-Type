/**
 * @file ProjectilePreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the projectile.
 * @copyright Epitech Rennes 2022
 */

#ifndef PROJECTILEPRELOAD_HPP
#define PROJECTILEPRELOAD_HPP

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
     * @brief Preloads the projectile.
     * @class ProjectilePreload
     */
    class ProjectilePreload : public EntityPreload
    {
        public:
            /**
             * @struct Projectile
             * @brief struct of the projectile.
             */
            typedef struct ProjectileStats {
                    std::size_t damage = 0;
                    float velX = 0.0f;
                    float velY = 0.0f;
                    float rotation = 0.0f;
                    std::size_t syncIdPar = 0;
                    std::size_t syncId = 0;
            } ProjectileStats;

            /**
             * @brief Creates a shot
             * @fn static void createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, std::size_t damage)
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param windowsSize The size of the window.
             * @param screenSize The size of the screen.
             * @param damage The damage of the projectile.
             */
            static void createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize, std::shared_ptr<sf::Vector2f> screenSize, ProjectileStats projectile);
    };
}

#endif // PROJECTILEPRELOAD_HPP

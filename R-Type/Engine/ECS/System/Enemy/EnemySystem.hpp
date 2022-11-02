/**
 * @file EnemySystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of an enemy.
 * @copyright Epitech Rennes 2022
*/

#ifndef ENEMYSYSTEM_HPP
#define ENEMYSYSTEM_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Graphic/Graphic.hpp"
/// @endcond

#define RADIUS 50
#define SPEED_OSC 5

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief System of an enemy.
     * @class EnemySystem
    */
    class EnemySystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;

        public:
            /**
             * @brief EnemySystem constructor.
             * @fn EnemySystem(std::shared_ptr<sf::Clock> clock, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
             * @param clock A shared pointer to the clock of the game (for enemy animations, patterns and such).
             * @param window A shared pointer to the render window
             * @param screenSize A shared pointer to the screen size
            */
            EnemySystem(Graphic &graphic);
            /**
             * @brief EnemySystem destructor.
             * @fn ~EnemySystem()
            */
            ~EnemySystem() = default;
            /**
             * @brief Update the enemy system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
            */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // ENEMYSYSTEM_HPP

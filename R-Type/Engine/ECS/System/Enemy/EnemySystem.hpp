/**
 * @file EnemySystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of an enemy.
 * @copyright Epitech Rennes 2022
 */

#ifndef ENEMYSYSTEM_HPP
#define ENEMYSYSTEM_HPP

/// @cond
#include "Engine/ECS/System/ISystem.hpp"
/// @endcond

#define RADIUS 50
#define SPEED_OSC 6

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
            void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager);

        public:
            /**
             * @brief EnemySystem constructor.
             * @fn EnemySystem(std::shared_ptr<sf::Clock> clock)
             * @param clock The clock of the game (for enemy animations, patterns and such).
             */
            EnemySystem(std::shared_ptr<sf::Clock> clock);
            /**
             * @brief EnemySystem constructor.
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

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

#define RADIUS 225
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
            std::shared_ptr<std::size_t> _syncId;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;

            bool setRandIdPlayer(Pattern &pat, EntityManager &entityManager);
            void cthulhuPattern(size_t id, ComponentManager &componentManager, EntityManager &entityManager);
            void lifeChainPattern(std::size_t firstChainSpriteId, std::size_t lastChainSpriteId, ComponentManager &componentManager, EntityManager &entityManager);
            void chainPattern(std::size_t firstChainSpriteId, std::size_t lastChainSpriteId, std::size_t speedFactor, ComponentManager &componentManager, EntityManager &entityManager);
            void devourerPattern(size_t id, ComponentManager &componentManager, EntityManager &entityManager);

        public:
            /**
             * @brief EnemySystem constructor.
             * @fn EnemySystem(Graphic &graphic, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             */
            EnemySystem(Graphic &graphic, EntityManager &entityManager);
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

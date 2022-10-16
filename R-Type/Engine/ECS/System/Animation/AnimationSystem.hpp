/**
 * @file AnimationSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The Animation system
 * @copyright Epitech Rennes 2022
*/

#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

/// @cond
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Loader/Loader.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The Animation system
     * @class AnimationSystem
    */
    class AnimationSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<std::vector<sf::Sprite>> _sprites;
            std::map<std::size_t, float> _lastTime;
            std::map<std::size_t, float> _delay;

        public:
            /**
             * @brief AnimationSystem constructor
             * @fn AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites)
             * @param event A shared pointer to the event
             * @param clock A shared pointer to the clock
             * @param AnimationBuffer A shared pointer to Animation buffer
            */
            AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites);
            /**
             * @brief AnimationSystem destructor
             * @fn ~AnimationSystem()
            */
            ~AnimationSystem() = default;
            /**
             * @brief Update the AnimationSystem
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the ComponentManager
             * @param entityManager A reference to the EntityManager
            */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // ANIMATIONSYSTEM_HPP
/**
 * @file Input.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The engine's input.
 * @copyright Epitech Rennes 2022
 */

#ifndef INPUT_HPP
#define INPUT_HPP

/// @cond
#include "ECS/Component/ComponentManager.hpp"
#include "ECS/Entity/EntityManager.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The engine's input.
     * @class Input
     */
    class Input
    {
        private:
        public:
            /**
             * @brief Input constructor.
             * @class Input()
             */
            Input();
            /**
             * @brief Input destructor.
             * @class ~Input()
             */
            ~Input() = default;
            /**
             * @brief Check an input.
             * @class void checkInput(std::size_t id, sf::Keyboard::Key input, ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<sf::Clock> clock)
             * @param id The id of the input to check
             * @param input The input to check
             * @param componentManager A reference to the ComponentManager
             * @param entityManager A reference to the EntityManager
             * @param clocl A shared pointer to the clock
             */
            void checkInput(std::size_t id, sf::Keyboard::Key input, ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<sf::Clock> clock);
            /**
             * @brief Create a shot
             * @class void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage)
             * @param id The id of the input to check
             * @param componentManager A reference to the ComponentManager
             * @param pos The position of the shot
             * @param entityManager A reference to the EntityManager
             * @param damage The damage of the shot
             */
            void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage);
    };
}

#endif // INPUT_HPP

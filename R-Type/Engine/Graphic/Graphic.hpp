/**
 * @file Graphic.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The Engine graphics (SFML).
 * @copyright Epitech Rennes 2022
*/

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

/// @cond
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The Engine graphics (SFML).
     * @class Graphic
    */
    class Graphic
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;

        public:
            /**
             * @brief Graphic constructor.
             * @fn Graphic()
            */
            Graphic();
            /**
             * @brief Graphic destructor.
             * @fn Graphic()
            */
            ~Graphic() = default;
            /**
             * @brief Get a shared pointer to the render window.
             * @fn std::shared_ptr<sf::RenderWindow> getWindow()
             * @return A shared pointer to the render window.
            */
            std::shared_ptr<sf::RenderWindow> getWindow();
            /**
             * @brief Get a shared pointer to an event (input for example).
             * @fn std::shared_ptr<sf::Event> getEvent()
             * @return A shared pointer to the event.
            */
            std::shared_ptr<sf::Event> getEvent();
            /**
             * @brief Get a shared pointer to the game clock
             * @fn std::shared_ptr<sf::Clock> getClock()
             * @return A shared pointer to the clock.
            */
            std::shared_ptr<sf::Clock> getClock();
    };
}

#endif // GRAPHIC_HPP

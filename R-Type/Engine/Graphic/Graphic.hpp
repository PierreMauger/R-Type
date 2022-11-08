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
            std::shared_ptr<sf::Vector2f> _screenSize;
            sf::Vector2f _lastSize;
            bool _isFullscreen;

        public:
            /**
             * @brief Graphic constructor.
             * @fn Graphic()
             */
            Graphic();
            /**
             * @brief Graphic destructor.
             * @fn ~Graphic()
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
            /**
             * @brief Get the last window size.
             * @fn sf::Vector2f &getLastSize()
             * @return A reference to the last window size.
             */
            sf::Vector2f &getLastSize();
            /**
             * @brief Get the screen size.
             * @fn std::shared_ptr<sf::Vector2f> getScreenSize()
             * @return A shared pointer to the screen size.
             */
            std::shared_ptr<sf::Vector2f> getScreenSize();
            /**
             * @brief Check if the game is in full screen mode
             * @fn bool isFullscreen()
             * @return A boolean indicating if the game is in full screen mode
             */
            bool isFullscreen();
            /**
             * @brief Set the screen size
             * @fn void setScreenSize(sf::Vector2f screenSize)
             * @param screenSize The new screen size
             */
            void setScreenSize(sf::Vector2f screenSize);
            /**
             * @brief Set the last (current) window size
             * @fn void setLastSize(sf::Vector2f lastSize)
             * @param lastSize The new window size
             */
            void setLastSize(sf::Vector2f lastSize);
            /**
             * @brief Set the game in full screen or not
             * @fn void setFullscreen(bool isFullscreen)
             * @param isFullScreen Boolean setting the game in full screen or not
             */
            void setFullscreen(bool isFullscreen);
    };
}

#endif // GRAPHIC_HPP

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "Includes.hpp"

namespace eng
{
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
            Graphic();
            ~Graphic() = default;
            std::shared_ptr<sf::RenderWindow> getWindow();
            std::shared_ptr<sf::Event> getEvent();
            std::shared_ptr<sf::Clock> getClock();
            sf::Vector2f &getLastSize();
            std::shared_ptr<sf::Vector2f> getScreenSize();
            bool isFullscreen();
            void setScreenSize(sf::Vector2f screenSize);
            void setLastSize(sf::Vector2f lastSize);
            void setFullscreen(bool isFullscreen);
    };
}

#endif // GRAPHIC_HPP

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
            sf::Vector2f _screenSize;

        public:
            Graphic();
            ~Graphic() = default;
            std::shared_ptr<sf::RenderWindow> getWindow();
            std::shared_ptr<sf::Event> getEvent();
            std::shared_ptr<sf::Clock> getClock();
            sf::Vector2f &getScreenSize();
    };
}

#endif // GRAPHIC_HPP

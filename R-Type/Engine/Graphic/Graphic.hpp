#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "Includes.hpp"

namespace eng
{
    class Graphic
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Event _event;

        public:
            Graphic();
            ~Graphic() = default;

            std::shared_ptr<sf::RenderWindow> &getWindow();
            sf::Event &getEvent();
    };
}

#endif // GRAPHIC_HPP

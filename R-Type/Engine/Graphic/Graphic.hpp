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
            bool isOpen();
            void display();
            void close();
            bool pollEvent();
            void clear(const sf::Color &color = sf::Color(0, 0, 0, 255));
    };
}

#endif // GRAPHIC_HPP

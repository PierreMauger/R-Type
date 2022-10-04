#include "Graphic.hpp"

using namespace eng;

Graphic::Graphic()
{
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "R-Type");
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
}

std::shared_ptr<sf::RenderWindow> &Graphic::getWindow()
{
    return this->_window;
}

sf::Event &Graphic::getEvent()
{
    return this->_event;
}

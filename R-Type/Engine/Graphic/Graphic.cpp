#include "Graphic.hpp"

using namespace eng;

Graphic::Graphic()
{
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "R-Type");
    this->_event = std::make_shared<sf::Event>();
    this->_clock = std::make_shared<sf::Clock>();
}

std::shared_ptr<sf::RenderWindow> Graphic::getWindow()
{
    return this->_window;
}

std::shared_ptr<sf::Event> Graphic::getEvent()
{
    return this->_event;
}

std::shared_ptr<sf::Clock> Graphic::getClock()
{
    return this->_clock;
}

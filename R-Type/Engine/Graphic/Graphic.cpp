#include "Graphic.hpp"

using namespace eng;

Graphic::Graphic()
{
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "R-Type");
    this->_screenSize = std::make_shared<sf::Vector2f>(this->_window->getSize().x, this->_window->getSize().x);
    this->_lastSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    this->_event = std::make_shared<sf::Event>();
    this->_clock = std::make_shared<sf::Clock>();
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
    while (this->_window->pollEvent(*this->_event)) {
        if (this->_event->type == sf::Event::Resized) {
            this->_screenSize->x = this->_event->size.width;
            this->_screenSize->y = this->_event->size.height;
            this->_lastSize = sf::Vector2f(this->_event->size.width, this->_event->size.height);
        }
    }
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

sf::Vector2f &Graphic::getLastSize()
{
    return this->_lastSize;
}

void Graphic::setLastSize(sf::Vector2f lastSize)
{
    this->_lastSize = lastSize;
}

std::shared_ptr<sf::Vector2f> Graphic::getScreenSize()
{
    return this->_screenSize;
}

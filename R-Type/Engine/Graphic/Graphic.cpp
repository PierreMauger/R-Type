#include "Graphic.hpp"

using namespace eng;

Graphic::Graphic()
{
    this->_isFullscreen = true;
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "R-Type", sf::Style::Fullscreen);
    this->_screenSize = std::make_shared<sf::Vector2f>(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    this->_lastSize = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    this->_event = std::make_shared<sf::Event>();
    this->_clock = std::make_shared<sf::Clock>();
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(true);
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

bool Graphic::isFullscreen()
{
    return this->_isFullscreen;
}

void Graphic::setFullscreen(bool isFullscreen)
{
    this->_isFullscreen = isFullscreen;
}

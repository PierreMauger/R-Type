#include "Graphic.hpp"

using namespace eng;

Graphic::Graphic()
{
    this->_isFullscreen = true;
    this->_sceneId = std::make_shared<std::size_t>(0);
    this->_port = std::make_shared<std::size_t>(0);
    this->_ip = std::make_shared<std::string>("");
    this->_isLocal = std::make_shared<bool>(false);
    this->_isReady = std::make_shared<bool>(false);
    this->_syncId = std::make_shared<std::size_t>(0);

    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "R-Type", sf::Style::Fullscreen);
    this->_screenSize = std::make_shared<sf::Vector2f>(1920, 1080);
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

std::shared_ptr<std::size_t> Graphic::getSceneId()
{
    return this->_sceneId;
}

std::shared_ptr<std::size_t> Graphic::getPort()
{
    return this->_port;
}

std::shared_ptr<std::string> Graphic::getIp()
{
    return this->_ip;
}

std::shared_ptr<bool> Graphic::getIsLocal()
{
    return this->_isLocal;
}

std::shared_ptr<bool> Graphic::getIsReady()
{
    return this->_isReady;
}

std::shared_ptr<std::size_t> Graphic::getSyncId()
{
    return this->_syncId;
}

std::shared_ptr<std::size_t> Graphic::getRoomPlayerNb()
{
    return this->_roomPlayerNb;
}

std::shared_ptr<std::size_t> Graphic::getRoomPlayerMax()
{
    return this->_roomPlayerMax;
}

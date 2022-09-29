#include "Graphic.hpp"

using namespace rdr;

Graphic::Graphic()
{
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "R-Type");
}

std::shared_ptr<sf::RenderWindow> &Graphic::getWindow()
{
    return this->window;
}

sf::Event &Graphic::getEvent()
{
    return this->event;
}

bool Graphic::isOpen()
{
    return this->window->isOpen();
}

void Graphic::close()
{
    this->window->close();
}

void Graphic::display()
{
    this->window->display();
}

void Graphic::clear(const sf::Color &color)
{
    this->window->clear(color);
}

bool Graphic::pollEvent(sf::Event &event)
{
    return this->window->pollEvent(event);
}

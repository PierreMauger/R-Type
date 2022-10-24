#include "Engine/ECS/System/Click/ClickSystem.hpp"

using namespace eng;

ClickSystem::ClickSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
{
    this->_window = window;
    this->_screenSize = screenSize;
}

void ClickSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();

    for (std::size_t i = 0; i < masks.size(); i++) {
    }
}

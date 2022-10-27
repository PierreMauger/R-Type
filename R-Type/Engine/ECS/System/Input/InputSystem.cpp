#include "Engine/ECS/System/Input/InputSystem.hpp"

#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"

using namespace eng;

InputSystem::InputSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
{
    this->_event = event;
    this->_clock = clock;
    this->_window = window;
    this->_screenSize = screenSize;
}

void InputSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t input = (InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);
    std::size_t app = (InfoComp::APP);
    std::size_t dis = (InfoComp::DIS);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || (masks[i].value() & input) != input || ((masks[i].value() & app) == app && componentManager.getSingleComponent<Appearance>(i).app) ||
            ((masks[i].value() & dis) == dis && componentManager.getSingleComponent<Disappearance>(i).dis))
            continue;
        Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
        CooldownShoot &sht = componentManager.getSingleComponent<CooldownShoot>(i);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > sht.lastShoot) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, i, 2);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > (sht.lastShoot - (sht.shootDelay / 2))) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, i, 1);
        }
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = vel.baseSpeedX * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = vel.baseSpeedX : vel.x = 0);
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = vel.baseSpeedY * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = vel.baseSpeedY : vel.y = 0);
    }
}

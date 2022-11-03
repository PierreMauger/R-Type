#include "Engine/ECS/System/Input/InputSystem.hpp"

using namespace eng;

InputSystem::InputSystem(Graphic &graphic, EntityManager &entityManager)
{
    this->_event = graphic.getEvent();
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();

    entityManager.addMaskCategory(InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);
}

void InputSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t input = (InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);
    std::size_t app = (InfoComp::APP);
    std::size_t dis = (InfoComp::DIS);

    for (auto id : entityManager.getMaskCategory(input)) {
        if (((masks[id].value() & app) == app && componentManager.getSingleComponent<Appearance>(id).app) || ((masks[id].value() & dis) == dis && componentManager.getSingleComponent<Disappearance>(id).dis))
            continue;
        Velocity &vel = componentManager.getSingleComponent<Velocity>(id);
        CooldownShoot &sht = componentManager.getSingleComponent<CooldownShoot>(id);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > sht.lastShoot) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, id, 2);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > (sht.lastShoot - (sht.shootDelay / 2))) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, id, 1);
        }
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = vel.baseSpeedX * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = vel.baseSpeedX : vel.x = 0);
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = vel.baseSpeedY * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = vel.baseSpeedY : vel.y = 0);
    }
}

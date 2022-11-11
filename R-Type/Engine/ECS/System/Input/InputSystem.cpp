#include "Engine/ECS/System/Input/InputSystem.hpp"

using namespace eng;

InputSystem::InputSystem(Graphic &graphic, EntityManager &entityManager)
{
    this->_event = graphic.getEvent();
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();

    entityManager.addMaskCategory(this->_controlTag);
    entityManager.addMaskCategory(this->_buttonTag);
}

void InputSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t app = (InfoComp::APP);
    std::size_t dis = (InfoComp::DIS);

    for (auto id : entityManager.getMaskCategory(this->_controlTag)) {
        if ((entityManager.hasMask(id, app) && componentManager.getSingleComponent<Appearance>(id).app) || (entityManager.hasMask(id, dis) && componentManager.getSingleComponent<Disappearance>(id).dis))
            continue;
        Velocity &vel = componentManager.getSingleComponent<Velocity>(id);
        CooldownShoot &sht = componentManager.getSingleComponent<CooldownShoot>(id);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > sht.lastShoot) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, id, {2, 15, 0, 0});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > (sht.lastShoot - (sht.shootDelay / 2))) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, id, {1, 15, 0, 0});
        }
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = vel.baseSpeedX * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = vel.baseSpeedX : vel.x = 0);
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = vel.baseSpeedY * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = vel.baseSpeedY : vel.y = 0);
    }

    for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
        Button button = componentManager.getSingleComponent<Button>(id);
        Text &text = componentManager.getSingleComponent<Text>(id);

        if (button.type != ButtonType::TEXTZONE || !button.selected)
            continue;
        for (int i = 0; i < 9; i++)
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(static_cast<int>(sf::Keyboard::Num0) + i)) && _event->type == sf::Event::KeyPressed && text.str.size() < button.maxSize)
                text.str += std::to_string(i);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period) && _event->type == sf::Event::KeyPressed && text.str.size() < button.maxSize)
            text.str += ".";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && _event->type == sf::Event::KeyPressed && text.str.size() > 0)
            text.str = text.str.substr(0, text.str.size() - 1);
    }
}

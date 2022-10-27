#include "Engine/ECS/System/Input/InputSystem.hpp"

using namespace eng;

InputSystem::InputSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
{
    this->_event = event;
    this->_clock = clock;
    this->_window = window;
    this->_screenSize = screenSize;
}

void InputSystem::createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage)
{
    auto &masks = entityManager.getMasks();
    std::size_t sizeMask = (InfoComp::SIZE | InfoComp::COOLDOWNSHOOT);
    Size size;
    sf::Vector2f sizeFire = sf::Vector2f(55 / this->_screenSize->x * _window->getSize().x, 30 / this->_screenSize->y * _window->getSize().y);
    CooldownShoot sizeProj;
    std::size_t addEntity = entityManager.addMask(
        (InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::PROJECTILE | InfoComp::SIZE | InfoComp::SPRITEAT),
        componentManager);

    if (masks[id].has_value() && (masks[id].value() & sizeMask) == sizeMask) {
        size = componentManager.getSingleComponent<Size>(id);
        sizeProj = componentManager.getSingleComponent<CooldownShoot>(id);
    }
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((damage == 2) ? 4 : 3), Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(
            addEntity,
            SpriteAttribut{0, {0, 0, 55, 30}, sf::Color::White, {(sizeProj.size / _screenSize->x * _window->getSize().x), sizeProj.size / _screenSize->y * _window->getSize().y}});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x, pos.y + size.y / 2 - sizeFire.y / 2, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{15 / static_cast<float>(sf::VideoMode::getDesktopMode().width) * _window->getSize().x, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, damage, sizeProj.size});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{sizeFire.x, sizeFire.y});
    addEntity = entityManager.addMask((InfoComp::SOUNDID), componentManager);
    sizeProj.size == 1 ? componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, 1})
                       : componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, 1 - (sizeProj.size / 10)});
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
        Position &pos = componentManager.getSingleComponent<Position>(i);
        Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
        CooldownShoot &sht = componentManager.getSingleComponent<CooldownShoot>(i);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > sht.lastShoot) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            createShoot(i, componentManager, pos, entityManager, 2);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > (sht.lastShoot - (sht.shootDelay / 2))) {
            sht.lastShoot = _clock->getElapsedTime().asSeconds() + sht.shootDelay;
            createShoot(i, componentManager, pos, entityManager, 1);
        }
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = vel.baseSpeedX * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = vel.baseSpeedX : vel.x = 0);
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = vel.baseSpeedY * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = vel.baseSpeedY : vel.y = 0);
    }
}

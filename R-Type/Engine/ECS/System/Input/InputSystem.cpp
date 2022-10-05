#include "Engine/ECS/System/Input/InputSystem.hpp"

using namespace eng;

InputSystem::InputSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock)
{
    this->_event = event;
    this->_clock = clock;
}

void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager)
{
    entityManager.addMask(id, (eng::InfoEntity::SPRITEID) | (eng::InfoEntity::POS) | (eng::InfoEntity::VEL) | (eng::InfoEntity::PARENT));
    componentManager.initEmptyComponent();
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{2});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x + 55, pos.y + 45, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{20, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(id, Parent{id});
}

void InputSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &controllable = componentManager.getComponent(typeid(Controllable));
    Component &velocity = componentManager.getComponent(typeid(Velocity));
    Component &speed = componentManager.getComponent(typeid(Speed));
    Component &position = componentManager.getComponent(typeid(Position));
    Component &cooldown = componentManager.getComponent(typeid(CooldownShoot));

    for (std::size_t i = 0; i < controllable.getSize(); i++) {
        if (controllable.getField(i).has_value()) {
            Speed &spd = std::any_cast<Speed &>(speed.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            CooldownShoot &sht = std::any_cast<CooldownShoot &>(cooldown.getField(i).value());
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _clock->getElapsedTime().asSeconds() > sht.time) {
                sht.time = _clock->getElapsedTime().asSeconds() + sht.cooldown;
                createShoot(controllable.getSize(), componentManager, std::any_cast<Position>(position.getField(i).value()), entityManager);
            }
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = spd.speed * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = spd.speed : vel.x = 0);
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = spd.speed * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = spd.speed : vel.y = 0);
        }
    }
}

#include "Engine/ECS/System/Input/InputSystem.hpp"

using namespace eng;

InputSystem::InputSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock)
{
    this->_event = event;
    this->_clock = clock;
}

void InputSystem::createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage)
{
    auto &masks = entityManager.getMasks();
    std::size_t sizeMask = (InfoComp::SIZE | InfoComp::COOLDOWNSHOOT);
    Size size;
    CooldownShoot sizeProj;

    if (masks[id].has_value() && (masks[id].value() & sizeMask) == sizeMask) {
        size = componentManager.getSingleComponent<Size>(id);
        sizeProj = componentManager.getSingleComponent<CooldownShoot>(id);
    }
    std::size_t addEntity = entityManager.addMask(
        (InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::PROJECTILE | InfoComp::SIZE), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((damage == 2) ? 4 : 3), Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + (size.y / 2 - (30 * sizeProj.size / 2)), pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{15, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, damage, sizeProj.size});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{55 * sizeProj.size, 30 * sizeProj.size});
    addEntity = entityManager.addMask((InfoComp::SOUNDID), componentManager);
    sizeProj.size == 1 ? componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, 1})
                       : componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, 1 - (sizeProj.size / 10)});
}

void InputSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t input = (InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & input) == input) {
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
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? vel.x = vel.baseSpeed * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? vel.x = vel.baseSpeed : vel.x = 0);
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? vel.y = vel.baseSpeed * -1 : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? vel.y = vel.baseSpeed : vel.y = 0);
        }
    }
}

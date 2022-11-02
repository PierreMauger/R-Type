#include "Input.hpp"

using namespace eng;

Input::Input()
{
}

void Input::createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage)
{
    auto &masks = entityManager.getMasks();
    std::size_t sizeMask = (InfoComp::SIZE | InfoComp::COOLDOWNSHOOT);
    Size size;
    CooldownShoot sizeProj;

    if (masks[id].has_value() && (masks[id].value() & sizeMask) == sizeMask) {
        size = componentManager.getSingleComponent<Size>(id);
        sizeProj = componentManager.getSingleComponent<CooldownShoot>(id);
    }
    std::size_t addEntity = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::PROJECTILE | InfoComp::SIZE), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((damage == 2) ? 4 : 3), Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + (size.y / 2 - (30 * sizeProj.size / 2)), pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{15, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, damage, sizeProj.size});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{55 * sizeProj.size, 30 * sizeProj.size});
    addEntity = entityManager.addMask((InfoComp::SOUNDID), componentManager);
    sizeProj.size == 1 ? componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, 1}) : componentManager.getComponent(typeid(SoundID)).emplaceData(addEntity, SoundID{2, false, false, 1 - (sizeProj.size / 10)});
}

void Input::checkInput(std::size_t id, sf::Keyboard::Key input, ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<sf::Clock> clock)
{
    std::size_t inputMask = (InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);

    if (entityManager.getMasks()[id].has_value() && (entityManager.getMasks()[id].value() & inputMask) == inputMask) {
        Position &pos = componentManager.getSingleComponent<Position>(id);
        Velocity &vel = componentManager.getSingleComponent<Velocity>(id);
        CooldownShoot &sht = componentManager.getSingleComponent<CooldownShoot>(id);
        if (input == sf::Keyboard::Key::Left)
            vel.x = vel.baseSpeedX * -1;
        if (input == sf::Keyboard::Key::Right)
            vel.x = vel.baseSpeedX;
        if (input == sf::Keyboard::Key::Up)
            vel.y = vel.baseSpeedY * -1;
        if (input == sf::Keyboard::Key::Down)
            vel.y = vel.baseSpeedY;
        if (input == sf::Keyboard::Key::Enter && clock->getElapsedTime().asSeconds() > sht.lastShoot) {
            sht.lastShoot = clock->getElapsedTime().asSeconds() + sht.shootDelay;
            this->createShoot(id, componentManager, pos, entityManager, 2);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && clock->getElapsedTime().asSeconds() > (sht.lastShoot - (sht.shootDelay / 2))) {
            sht.lastShoot = clock->getElapsedTime().asSeconds() + sht.shootDelay;
            this->createShoot(id, componentManager, pos, entityManager, 1);
        }
    }
}

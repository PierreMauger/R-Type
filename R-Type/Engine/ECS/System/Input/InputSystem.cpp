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
    std::size_t addEntity = masks.size();
    std::size_t sizeMask = (InfoEntity::SIZE);
    Size size;

    if (masks[id].has_value() && (masks[id].value() & sizeMask) == sizeMask)
        size = std::any_cast<Size &>(componentManager.getComponent(typeid(Size)).getField(id).value());
    entityManager.addManualMask(addEntity,
                                (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARENT | eng::InfoEntity::PROJECTILE |
                                 eng::InfoEntity::PROJECTILE | eng::InfoEntity::SIZE),
                                componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{static_cast<std::size_t>((damage == 2) ? 4 : 3), Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{15, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, damage});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{55, 30});
}

void InputSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t input = (InfoEntity::CONTROLLABLE | InfoEntity::VEL | InfoEntity::POS | InfoEntity::COOLDOWNSHOOT | InfoEntity::SIZE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & input) == input) {
            Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(componentManager.getComponent(typeid(Velocity)).getField(i).value());
            CooldownShoot &sht = std::any_cast<CooldownShoot &>(componentManager.getComponent(typeid(CooldownShoot)).getField(i).value());
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
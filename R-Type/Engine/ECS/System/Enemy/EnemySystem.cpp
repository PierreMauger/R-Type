#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

using namespace eng;

EnemySystem::EnemySystem(std::shared_ptr<sf::Clock> clock)
{
    this->_clock = clock;
}

void EnemySystem::createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager)
{
    std::size_t addEntity = componentManager.getComponent(typeid(Position)).getSize();
    Size size = std::any_cast<Size>(componentManager.getComponent(typeid(Size)).getField(id).value());

    entityManager.addMask(addEntity, (eng::InfoEntity::SPRITEID) | (eng::InfoEntity::POS) | (eng::InfoEntity::VEL) | (eng::InfoEntity::PARENT) | (eng::InfoEntity::PROJECTILE) |
                                         (eng::InfoEntity::PROJECTILE));
    componentManager.initEmptyComponent();
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{1, Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{-15, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true});
}

void EnemySystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    Component &position = componentManager.getComponent(typeid(Position));
    Component &velocity = componentManager.getComponent(typeid(Velocity));
    Component &patern = componentManager.getComponent(typeid(Patern));
    Component &enemy = componentManager.getComponent(typeid(Enemy));
    Component &appear = componentManager.getComponent(typeid(Appearance));

    for (std::size_t i = 0; i < position.getSize(); i++) {
        if (appear.getField(i).has_value())
            if (std::any_cast<Appearance &>(appear.getField(i).value()).app)
                continue;
        if (position.getField(i).has_value() && velocity.getField(i).has_value() && patern.getField(i).has_value()) {
            Position &pos = std::any_cast<Position &>(position.getField(i).value());
            Velocity &vel = std::any_cast<Velocity &>(velocity.getField(i).value());
            Patern &pat = std::any_cast<Patern &>(patern.getField(i).value());
            pos.x += vel.x;
            if (pat.type == TypePatern::OSCILLATION) {
                pos.y = pat.center + std::sin(pat.angle) * RADIUS;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC;
            }
            if (pat.type == TypePatern::BIGOSCILLATION) {
                pos.y = pat.center + std::sin(pat.angle) * (RADIUS * 3);
                pat.angle = this->_clock->getElapsedTime().asSeconds() * (SPEED_OSC / 2);
            }
            if (enemy.getField(i).has_value()) {
                Enemy &ene = std::any_cast<Enemy &>(enemy.getField(i).value());
                if (ene.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > ene.lastShoot + ene.shootDelay) {
                    createShoot(i, componentManager, pos, entityManager);
                    ene.lastShoot = _clock->getElapsedTime().asSeconds();
                }
            }
        }
    }
}
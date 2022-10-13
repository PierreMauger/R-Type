#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

using namespace eng;

EnemySystem::EnemySystem(std::shared_ptr<sf::Clock> clock)
{
    this->_clock = clock;
}

void EnemySystem::createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager)
{
    std::size_t addEntity = componentManager.getComponent(typeid(Position)).getSize();
    Size size = componentManager.getSingleComponent<Size>(id);

    entityManager.addManualMask(addEntity, (InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::PROJECTILE | InfoComp::SIZE),
                                componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{3, Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{-15, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{55, 30});
}

void EnemySystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t appear = (InfoComp::APP);
    std::size_t enemyData = (InfoComp::POS | InfoComp::VEL | InfoComp::PATERN);
    std::size_t enemy = (InfoComp::ENEMY);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || (masks[i].value() & appear) == appear && componentManager.getSingleComponent<Appearance>(i).app)
            continue;
        if ((masks[i].value() & enemyData) == enemyData) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
            Patern &pat = componentManager.getSingleComponent<Patern>(i);
            if (pat.type == TypePatern::CIRCLE) {
                pos.x = pat.center.x + std::cos(pat.angle) * (RADIUS * 2);
                pos.y = pat.center.y + std::sin(pat.angle) * (RADIUS * 2);
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC / 2;
            }
            if (pat.type == TypePatern::OSCILLATION) {
                pos.x += vel.x;
                pos.y = pat.center.y + std::sin(pat.angle) * RADIUS;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC;
            }
            if (pat.type == TypePatern::BIGOSCILLATION) {
                pos.x += vel.x;
                pos.y = pat.center.y + std::sin(pat.angle) * (RADIUS * 3);
                pat.angle = this->_clock->getElapsedTime().asSeconds() * (SPEED_OSC / 2);
            }
            if (pat.type == TypePatern::LINE)
                pos.x += vel.x;
            if ((masks[i].value() & enemy) == enemy) {
                Enemy &enemy = componentManager.getSingleComponent<Enemy>(i);
                if (enemy.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > enemy.lastShoot + enemy.shootDelay) {
                    createShoot(i, componentManager, pos, entityManager);
                    enemy.lastShoot = _clock->getElapsedTime().asSeconds();
                }
            }
        }
    }
}

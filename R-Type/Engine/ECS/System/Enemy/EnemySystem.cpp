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

    entityManager.addManualMask(addEntity,
                                (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARENT | eng::InfoEntity::PROJECTILE |
                                 eng::InfoEntity::PROJECTILE | eng::InfoEntity::SIZE),
                                componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{1, Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x + size.x / 2, pos.y + size.y / 2, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{-15, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{55, 30});
}

void EnemySystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t appear = (InfoEntity::APP);
    std::size_t enemyData = (InfoEntity::POS | InfoEntity::VEL | InfoEntity::PATERN);
    std::size_t enemy = (InfoEntity::ENEMY);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & appear) == appear && std::any_cast<Appearance &>(componentManager.getComponent(typeid(Appearance)).getField(i).value()).app) {
                continue;
            }
            if ((masks[i].value() & enemyData) == enemyData) {
                Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                Velocity &vel = std::any_cast<Velocity &>(componentManager.getComponent(typeid(Velocity)).getField(i).value());
                Patern &pat = std::any_cast<Patern &>(componentManager.getComponent(typeid(Patern)).getField(i).value());
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
                    Enemy &ene = std::any_cast<Enemy &>(componentManager.getComponent(typeid(Enemy)).getField(i).value());
                    if (ene.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > ene.lastShoot + ene.shootDelay) {
                        createShoot(i, componentManager, pos, entityManager);
                        ene.lastShoot = _clock->getElapsedTime().asSeconds();
                    }
                }
            }
        }
    }
}

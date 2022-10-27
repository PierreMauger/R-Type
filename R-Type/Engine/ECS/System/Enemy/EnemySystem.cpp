#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

using namespace eng;

EnemySystem::EnemySystem(std::shared_ptr<sf::Clock> clock, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
{
    this->_clock = clock;
    this->_window = window;
    this->_screenSize = screenSize;
}

void EnemySystem::createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager)
{
    std::size_t addEntity;
    Size size = componentManager.getSingleComponent<Size>(id);
    sf::Vector2f sizeFire = sf::Vector2f(55 / this->_screenSize->x * _window->getSize().x, 30 / this->_screenSize->y * _window->getSize().y);

    addEntity = entityManager.addMask(
        (InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARENT | InfoComp::PROJECTILE | InfoComp::PROJECTILE | InfoComp::SIZE | InfoComp::SPRITEAT),
        componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(addEntity, SpriteID{9, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(addEntity, SpriteAttribut{0, {0, 0, 55, 30}, sf::Color::White, {1 / _screenSize->x * _window->getSize().x, 1 / _screenSize->y * _window->getSize().y}});
    componentManager.getComponent(typeid(Position)).emplaceData(addEntity, Position{pos.x, pos.y + size.y / 2 - sizeFire.y / 2, pos.z});
    componentManager.getComponent(typeid(Velocity)).emplaceData(addEntity, Velocity{15 / this->_screenSize->x * _window->getSize().x * -1, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(addEntity, Parent{id});
    componentManager.getComponent(typeid(Projectile)).emplaceData(addEntity, Projectile{true, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(addEntity, Size{sizeFire.x, sizeFire.y});
}

void EnemySystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t appear = (InfoComp::APP);
    std::size_t enemyData = (InfoComp::POS | InfoComp::VEL | InfoComp::PATERN);
    std::size_t enemy = (InfoComp::ENEMY);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || ((masks[i].value() & appear) == appear && componentManager.getSingleComponent<Appearance>(i).app))
            continue;
        if ((masks[i].value() & enemyData) == enemyData) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
            Pattern &pat = componentManager.getSingleComponent<Pattern>(i);
            if (pat.type == TypePattern::CIRCLE) {
                vel.x = (std::cos(pat.angle) * SPEED_OSC) / this->_screenSize->x * _window->getSize().x;
                vel.y = (std::sin(pat.angle) * SPEED_OSC) / this->_screenSize->y * _window->getSize().y;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC / 2;
            }
            if (pat.type == TypePattern::OSCILLATION) {
                vel.y = (std::sin(pat.angle) * SPEED_OSC) / this->_screenSize->y * _window->getSize().y;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC;
            }
            if (pat.type == TypePattern::BIGOSCILLATION) {
                vel.y = (std::sin(pat.angle) * SPEED_OSC) / this->_screenSize->y * _window->getSize().y;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC / 3;
            }
            if (pat.type == TypePattern::LINE)
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

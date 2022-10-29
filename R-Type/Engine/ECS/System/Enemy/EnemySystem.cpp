#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"

using namespace eng;

EnemySystem::EnemySystem(std::shared_ptr<sf::Clock> clock, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
{
    this->_clock = clock;
    this->_window = window;
    this->_screenSize = screenSize;
}

void EnemySystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t appear = (InfoComp::APP);
    std::size_t enemyData = (InfoComp::POS | InfoComp::VEL | InfoComp::PATTERN);
    std::size_t cooldownEnemy = (InfoComp::COOLDOWNSHOOT);
    std::size_t devourer = (InfoComp::GROUPEN | InfoComp::POS);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || ((masks[i].value() & appear) == appear && componentManager.getSingleComponent<Appearance>(i).app))
            continue;
        if ((masks[i].value() & enemyData) == enemyData) {
            Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
            Pattern &pat = componentManager.getSingleComponent<Pattern>(i);
            if (pat.type == TypePattern::DEVOUREROSC) {
                // TODO: U-turn when reaching the end of the screen
                if (masks[i].has_value() && ((masks[i].value() & devourer) == devourer) && componentManager.getSingleComponent<GroupEntity>(i).entityId == 0) {
                    componentManager.getSingleComponent<GroupEntity>(i).lastPos.y = componentManager.getSingleComponent<Position>(i).y;
                    componentManager.getSingleComponent<Position>(i).y = (500 / this->_screenSize->x * _window->getSize().x) + std::sin(pat.angle) * RADIUS;
                    pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC / 1.5;
                }
            }
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
            if ((masks[i].value() & cooldownEnemy) == cooldownEnemy) {
                CooldownShoot &clEnemy = componentManager.getSingleComponent<CooldownShoot>(i);
                if (clEnemy.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > clEnemy.lastShoot + clEnemy.shootDelay) {
                    ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, i, 1);
                    clEnemy.lastShoot = _clock->getElapsedTime().asSeconds();
                }
            }
        }
    }
}

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
    std::size_t enemyData = (InfoComp::POS | InfoComp::VEL | InfoComp::PATERN);
    std::size_t cooldownEnemy = (InfoComp::COOLDOWNSHOOT);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || ((masks[i].value() & appear) == appear && componentManager.getSingleComponent<Appearance>(i).app))
            continue;
        if ((masks[i].value() & enemyData) == enemyData) {
            Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
            Patern &pat = componentManager.getSingleComponent<Patern>(i);
            if (pat.type == TypePatern::CIRCLE) {
                vel.x = (std::cos(pat.angle) * SPEED_OSC) / this->_screenSize->x * _window->getSize().x;
                vel.y = (std::sin(pat.angle) * SPEED_OSC) / this->_screenSize->y * _window->getSize().y;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC / 2;
            }
            if (pat.type == TypePatern::OSCILLATION) {
                vel.y = (std::sin(pat.angle) * SPEED_OSC) / this->_screenSize->y * _window->getSize().y;
                pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC;
            }
            if (pat.type == TypePatern::BIGOSCILLATION) {
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

#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

using namespace eng;

EnemySystem::EnemySystem(Graphic &graphic, [[maybe_unused]] EntityManager &entityManager)
{
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
}

void EnemySystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t appear = (InfoComp::APP);
    std::size_t enemyData = (InfoComp::POS | InfoComp::VEL | InfoComp::PATTERN);
    std::size_t cooldownEnemy = (InfoComp::COOLDOWNSHOOT);
    std::size_t eneParent = (InfoComp::PARENT | InfoComp::POS);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value() || ((masks[i].value() & appear) == appear && componentManager.getSingleComponent<Appearance>(i).app))
            continue;
        if ((masks[i].value() & eneParent) == eneParent && componentManager.getSingleComponent<Parent>(i).follow == true) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            Position &parentPos = componentManager.getSingleComponent<Position>(componentManager.getSingleComponent<Parent>(i).id);
            pos.x = parentPos.x;
            pos.y = parentPos.y;
            continue;
        }
        if ((masks[i].value() & enemyData) == enemyData) {
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
            if (pat.type == TypePattern::EIGHT) {
                
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

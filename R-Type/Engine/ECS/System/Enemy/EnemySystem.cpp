#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

using namespace eng;

EnemySystem::EnemySystem(Graphic &graphic, [[maybe_unused]] EntityManager &entityManager)
{
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
}

bool EnemySystem::setRandIdPlayer(Pattern &pat, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::vector<size_t> idPlayers;
    std::size_t spriteMask = (InfoComp::SPRITEID | InfoComp::SPRITEAT);
    std::size_t contMask = (InfoComp::CONTROLLABLE | InfoComp::VEL);

    if (entityManager.getMaskCategory(spriteMask).size() == 0)
        return false;
    for (auto &id : entityManager.getMaskCategory(spriteMask))
        if (masks[id].has_value() && (masks[id].value() & contMask) == contMask)
            idPlayers.push_back(id);
    if (idPlayers.size() == 0)
        return false;
    pat.focusEntity = idPlayers[rand() % idPlayers.size()];
    return true;
}

void EnemySystem::cthulhuPattern(size_t id, ComponentManager &componentManager, EntityManager &entityManager)
{
    Velocity &vel = componentManager.getSingleComponent<Velocity>(id);
    Pattern &pat = componentManager.getSingleComponent<Pattern>(id);
    Position &pos = componentManager.getSingleComponent<Position>(id);
    Life &life = componentManager.getSingleComponent<Life>(id);
    CooldownShoot &clEnemy = componentManager.getSingleComponent<CooldownShoot>(id);
    SpriteAttribut &spriteAttribut = componentManager.getSingleComponent<SpriteAttribut>(id);
    SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(id);
    Position posPlayer = {0, 0, 0};
    auto &masks = entityManager.getMasks();

    float delayIdle = 1;
    float delayTransform = 3;
    float delayShoot = 5;
    float delayAttack = 1.5;
    float delayMove = 2;
    bool checkPlayer = true;

    // Set the elapsed time at the beginning of the game
    if (pat.statusTime == 0)
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();

    // Phase 2 Event
    if (life.life <= life.defaultLife / 2 && pat.phase == PHASE01) {
        pat.status = TypeStatus::TRANSFORM;
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();
        pat.phase = PHASE02;
    }

    // Reset player id if the player is dead
    if (!masks[pat.focusEntity].has_value()) {
        setRandIdPlayer(pat, entityManager);
        return;
    }

    // Pattern Status Part
    switch (pat.status) {
        case TypeStatus::SEARCH :
            pat.status = TypeStatus::IDLE;
            if (!this->setRandIdPlayer(pat, entityManager)) {
                pat.status = TypeStatus::SEARCH;
                checkPlayer = false;
            }
            vel.x = 0;
            vel.y = 0;
            break;

        case TypeStatus::IDLE :
            if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayIdle) {
                pat.status = TypeStatus::SHOOT;
                if (pat.phase == PHASE02) {
                    pat.status = TypeStatus::ATTACK;
                    if (checkPlayer)
                        pat.lastPosFocus = componentManager.getSingleComponent<Position>(pat.focusEntity);
                }
                pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            }
            vel.x = 0;
            vel.y = 0;
            pat.status = IDLE;
            break;

        case TypeStatus::MOVE :
            if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayMove) {
                pat.status = TypeStatus::SHOOT;
                pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            }
            if (checkPlayer) {
                posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
                vel.x = (posPlayer.x - pos.x) / 100;
                vel.y = (posPlayer.y - pos.y) / 100;
            }
            break;

        case TypeStatus::SHOOT :
            if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayShoot) {
                pat.status = TypeStatus::SEARCH;
                pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            }
            vel.x = (std::cos(pat.angle) * SPEED_OSC) / this->_screenSize->x * _window->getSize().x;
            vel.y = (std::sin(pat.angle) * SPEED_OSC) / this->_screenSize->y * _window->getSize().y;
            pat.angle = this->_clock->getElapsedTime().asSeconds() * SPEED_OSC / 2;
            if (clEnemy.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > clEnemy.lastShoot + clEnemy.shootDelay) {
                ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, id, 1);
                clEnemy.lastShoot = _clock->getElapsedTime().asSeconds();
            }
            break;

        case TypeStatus::ATTACK :
            if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayAttack) {
                pat.status = TypeStatus::SEARCH;
                pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            }
            vel.x = (pat.lastPosFocus.x - pos.x) / 20;
            vel.y = (pat.lastPosFocus.y - pos.y) / 20;
            break;

        case TypeStatus::TRANSFORM :
            if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayTransform) {
                pat.status = TypeStatus::SEARCH;
                pat.statusTime = this->_clock->getElapsedTime().asSeconds();
                spriteID = SpriteID{20, Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 110, 0};
                spriteAttribut.rect = {0, 0, 110, 146};
            }
            checkPlayer = false;
            spriteAttribut.rotation += (this->_clock->getElapsedTime().asSeconds() - pat.statusTime) * 10;
            vel.x = 0;
            vel.y = 0;
            break;

        default :
            pat.status = TypeStatus::SEARCH;
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            break;
    }

    // Rotation Part
    if (checkPlayer) {
        posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
        spriteAttribut.rotation = (atan2(posPlayer.y - pos.y, posPlayer.x - pos.x) * 180 / M_PI) - 90;
    }
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

        if ((masks[i].value() & enemyData) != enemyData)
            continue;

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
        if (pat.type == TypePattern::CTHULHU) {
            this->cthulhuPattern(i, componentManager, entityManager);
            continue;
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

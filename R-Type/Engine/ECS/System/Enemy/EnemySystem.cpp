#include "Engine/ECS/System/Enemy/EnemySystem.hpp"

using namespace eng;

EnemySystem::EnemySystem(Graphic &graphic, [[maybe_unused]] EntityManager &entityManager)
{
    this->_syncId = graphic.getSyncId();
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
}

bool EnemySystem::setRandIdPlayer(Pattern &pat, EntityManager &entityManager)
{
    std::vector<size_t> idPlayers;
    std::size_t spriteMask = (InfoComp::SPRITEID | InfoComp::SPRITEAT);
    std::size_t contMask = (InfoComp::CONTROLLABLE | InfoComp::VEL);

    if (entityManager.getMaskCategory(spriteMask).size() == 0)
        return false;
    for (auto &id : entityManager.getMaskCategory(spriteMask))
        if (entityManager.hasMask(id, contMask))
            idPlayers.push_back(id);
    if (idPlayers.size() == 0)
        return false;
    pat.focusEntity = idPlayers[rand() % idPlayers.size()];
    return true;
}

void EnemySystem::lifeChainPattern(std::size_t firstChainSpriteId, std::size_t lastChainSpriteId, ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t baseId = 0;
    std::size_t chainId = 0;
    Chain chain;
    std::size_t dmgToGive = 0;

    for (std::size_t j = 0; j < masks.size(); j++) {
        if (!masks[j].has_value() || !entityManager.hasMask(j, InfoComp::CHAIN) || !entityManager.hasMask(j, InfoComp::LIFE))
            continue;
        chain = componentManager.getSingleComponent<Chain>(j);
        if (chain.partInfo == firstChainSpriteId) {
            baseId = j;
            break;
        }
    }
    chainId = baseId;
    if (chainId < masks.size() && !masks[chainId].has_value()) {
        std::cout << "Error: chainId is not valid : " << chainId << std::endl;
        return;
    }

    Life &life = componentManager.getSingleComponent<Life>(chainId);
    dmgToGive += life.defaultLife - life.life;
    while (chain.nextId < masks.size() && chain.partInfo != lastChainSpriteId) {
        if (!masks[chain.nextId].has_value() || !entityManager.hasMask(chain.nextId, InfoComp::POS) || !entityManager.hasMask(chain.nextId, InfoComp::VEL) || !entityManager.hasMask(chain.nextId, InfoComp::LIFE)) {
            break;
        }
        life = componentManager.getSingleComponent<Life>(chain.nextId);
        dmgToGive += life.defaultLife - life.life;
        chainId = chain.nextId;
        chain = componentManager.getSingleComponent<Chain>(chain.nextId);
    }

    chainId = baseId;
    life = componentManager.getSingleComponent<Life>(chainId);
    life.life -= dmgToGive;
    while (chain.nextId < masks.size() && chain.partInfo != lastChainSpriteId) {
        if (!masks[chain.nextId].has_value() || !entityManager.hasMask(chain.nextId, InfoComp::POS) || !entityManager.hasMask(chain.nextId, InfoComp::VEL) || !entityManager.hasMask(chain.nextId, InfoComp::LIFE)) {
            break;
        }
        life = componentManager.getSingleComponent<Life>(chain.nextId);
        life.life -= dmgToGive;
        chain = componentManager.getSingleComponent<Chain>(chain.nextId);
    }
}

void EnemySystem::chainPattern(std::size_t firstChainSpriteId, std::size_t lastChainSpriteId, std::size_t speedFactor, ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    // sf::Vector2u windowsSize = this->_window->getSize();
    // float scal = 1.5;
    std::size_t chainId = 0;
    Chain chain;

    // Search the begin of the tail
    for (std::size_t j = 0; j < masks.size(); j++) {
        if (!masks[chain.nextId].has_value() || !entityManager.hasMask(j, InfoComp::CHAIN))
            continue;
        chain = componentManager.getSingleComponent<Chain>(j);
        if (chain.partInfo == firstChainSpriteId) {
            chainId = j;
            break;
        }
    }
    if (chainId < masks.size() && !masks[chainId].has_value()) {
        std::cout << "Error: chainId is not valid : " << chainId << std::endl;
        return;
    }

    if (chainId >= masks.size() || !masks[chainId].has_value() || !entityManager.hasMask(chainId, InfoComp::PATTERN) || !entityManager.hasMask(chainId, InfoComp::POS)) {
        return;
    }
    // get the pattern component of the head
    Pattern &pat = componentManager.getSingleComponent<Pattern>(chainId);

    while (chain.nextId < masks.size() && chain.partInfo != lastChainSpriteId) {
        if (!masks[chain.nextId].has_value() || !entityManager.hasMask(chain.nextId, InfoComp::POS) || !entityManager.hasMask(chain.nextId, InfoComp::VEL) || !entityManager.hasMask(chain.nextId, InfoComp::SPRITEID) || !entityManager.hasMask(chain.nextId, InfoComp::SPRITEAT) ||
            !entityManager.hasMask(chain.nextId, InfoComp::CHAIN)) {
            break;
        }
        Position lastPos = componentManager.getSingleComponent<Position>(chainId);
        Position &pos = componentManager.getSingleComponent<Position>(chain.nextId);
        Velocity &vel = componentManager.getSingleComponent<Velocity>(chain.nextId);
        SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(chain.nextId);
        SpriteAttribut &spriteAttribut = componentManager.getSingleComponent<SpriteAttribut>(chain.nextId);
        // Size &size = componentManager.getSingleComponent<Size>(chainId);

        // Change the sprite of the chain
        if (pat.status == TypeStatus::TRANSFORM) {
            spriteID = SpriteID{S_DEVOURER_BODY_S, Priority::MEDIUM, 0, 0, false, false, 0, 0, 0, 0};
            spriteAttribut.rect = {0, 0, 88, 114};
            // size = Size{(88 / _screenSize->x * windowsSize.x) * scal, (114 / _screenSize->y * windowsSize.y) * scal};
        }

        spriteAttribut.rotation = (atan2(lastPos.y - pos.y, lastPos.x - pos.x) * 180 / M_PI - 180);

        vel.x = (lastPos.x - pos.x) / speedFactor;
        vel.y = (lastPos.y - pos.y) / speedFactor;

        // update chain
        chainId = chain.nextId;
        chain = componentManager.getSingleComponent<Chain>(chain.nextId);
    }

    if (chainId >= masks.size() || !masks[chainId].has_value() || !entityManager.hasMask(chainId, InfoComp::SPRITEID) || !entityManager.hasMask(chainId, InfoComp::SPRITEAT)) {
        return;
    }
    // Change ID of the last sprite of the tail
    SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(chainId);
    SpriteAttribut &spriteAttribut = componentManager.getSingleComponent<SpriteAttribut>(chainId);
    // Size &size = componentManager.getSingleComponent<Size>(chainId);
    if (pat.status == TypeStatus::TRANSFORM) {
        spriteID = SpriteID{S_DEVOURER_TAIL_S, Priority::MEDIUM, 0, 0, false, false, 0, 0, 0, 0};
        spriteAttribut.rect = {0, 0, 148, 86};
        // size = Size{(148 / _screenSize->x * windowsSize.x) * scal, (86 / _screenSize->y * windowsSize.y) * scal};
        pat.status = TypeStatus::SEARCH;
    }
}

void EnemySystem::devourerPattern(size_t id, ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();

    if (id >= masks.size() || !masks[id].has_value() || !entityManager.hasMask(id, InfoComp::VEL) || !entityManager.hasMask(id, InfoComp::PATTERN) || !entityManager.hasMask(id, InfoComp::POS) || !entityManager.hasMask(id, InfoComp::LIFE) || !entityManager.hasMask(id, InfoComp::SPRITEAT) ||
        !entityManager.hasMask(id, InfoComp::SPRITEID)) {
        return;
    }

    Velocity &vel = componentManager.getSingleComponent<Velocity>(id);
    Pattern &pat = componentManager.getSingleComponent<Pattern>(id);
    Position &pos = componentManager.getSingleComponent<Position>(id);
    Life &life = componentManager.getSingleComponent<Life>(id);
    SpriteAttribut &spriteAttribut = componentManager.getSingleComponent<SpriteAttribut>(id);
    SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(id);
    // Size &size = componentManager.getSingleComponent<Size>(id);
    Position posPlayer = {0, 0, 0};
    // sf::Vector2u windowsSize = this->_window->getSize();
    std::size_t speedFactor = 6;
    // float scal = 1.5;

    // rand a position with the size of the screen
    float randTpX = (rand() % static_cast<int>(this->_screenSize->x));
    float posPairY = 0;

    float delayIdle = (rand() % 3) + 1;
    float delayAttack = 3;
    float delayMove = 10;
    float delayShoot = 3;

    bool checkPlayer = true;

    if (pat.statusTime == 0)
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();

    if (pat.focusEntity < masks.size() && !masks[pat.focusEntity].has_value()) {
        setRandIdPlayer(pat, entityManager);
        return;
    }

    // Phase 2 Event
    if (life.life <= life.defaultLife / 2 && pat.phase == PHASE01) {
        pat.status = TypeStatus::TRANSFORM;
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();
        pat.phase = TypePhase::PHASE02;
        pat.phaseCount = 4;
    }

    // Phase 1 && Phase 2 Attack && Phase 3 Rage Attack
    if (pat.phase == TypePhase::PHASE02) {
        if (pat.phaseCount == 0) {
            pat.phase = TypePhase::PHASE03;
            pat.phaseCount = 3;
        }
        speedFactor = 10;
    } else if (pat.phase == TypePhase::PHASE03) {
        if (pat.phaseCount == 0) {
            pat.phase = TypePhase::PHASE02;
            pat.status = TypeStatus::SEARCH;
            pat.phaseCount = 4;
        }
    }

    switch (pat.status) {
    case TypeStatus::SEARCH:
        pat.status = TypeStatus::MOVE;
        if (!this->setRandIdPlayer(pat, entityManager)) {
            pat.status = TypeStatus::SEARCH;
            checkPlayer = false;
        }
        break;

    case TypeStatus::IDLE:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayIdle) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            if (pat.phase == TypePhase::PHASE01) {
                pat.status = TypeStatus::MOVE;
            } else if (pat.phase == TypePhase::PHASE02) {
                pat.status = TypeStatus::ATTACK;
                pat.lastPosFocus.x = randTpX;
                spriteAttribut.rotation = (atan2(pat.lastPosFocus.y - pos.y, pat.lastPosFocus.x - pos.x) * 180 / M_PI - 180);
                checkPlayer = false;
                speedFactor = 1;
            }
            vel.x = 0;
            vel.y = 0;
            // sound teleport
        }
        break;

    case TypeStatus::MOVE:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayMove) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::SEARCH;
            if (pat.phase == TypePhase::PHASE02) {
                pat.lastPosFocus.x = randTpX;
                pat.status = TypeStatus::ATTACK;
                speedFactor = 1;
            }
        }
        if (checkPlayer && pat.focusEntity < masks.size() && masks[pat.focusEntity].has_value() && entityManager.hasMask(pat.focusEntity, InfoComp::POS)) {
            posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
            vel.x = ((posPlayer.x - 20) - pos.x) / 60;
            vel.y = ((posPlayer.y - 20) - pos.y) / 60;
        }
        break;

    case TypeStatus::SHOOT:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayShoot) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::MOVE;
            pat.phaseCount--;
        }
        break;

    case TypeStatus::ATTACK:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayAttack) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::IDLE;
            pat.phaseCount--;
        }
        if (pat.phaseCount % 2 == 0)
            posPairY = -200;
        else
            posPairY = this->_screenSize->y + 200;
        vel.x = (pat.lastPosFocus.x - pos.x) / 50;
        vel.y = (posPairY - pos.y) / 50;
        break;

    case TypeStatus::TRANSFORM: {
        spriteID = SpriteID{S_DEVOURER_HEAD_S, Priority::MEDIUM, 0, 0, false, false, 0, 0, 0, 0};
        spriteAttribut.rect = {0, 0, 196, 134};
        // size = Size{(196 / _screenSize->x * windowsSize.x) * scal, (134 / _screenSize->y * windowsSize.y) * scal};
        std::size_t soundId = entityManager.addMask((InfoComp::SOUNDID), componentManager);
        componentManager.getComponent(typeid(SoundID)).emplaceData(soundId, SoundID{2, false, false, 1});
        break;
    }

    default:
        pat.status = TypeStatus::SEARCH;
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();
        break;
    }

    if (checkPlayer && pat.focusEntity < masks.size() && masks[pat.focusEntity].has_value() && entityManager.hasMask(pat.focusEntity, InfoComp::POS)) {
        posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
        spriteAttribut.rotation = (atan2(posPlayer.y - pos.y, posPlayer.x - pos.x) * 180 / M_PI - 180);
    }
    chainPattern(S_DEVOURER_HEAD, S_DEVOURER_TAIL, speedFactor, componentManager, entityManager);
    lifeChainPattern(S_DEVOURER_HEAD, S_DEVOURER_TAIL, componentManager, entityManager);
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

    float delayIdle = 3;
    float delayTransform = 3;
    float delayShoot = 8;
    float delayAttack = 0.6;
    float delayMove = 2;

    // check if player is dead & used to stop rotation for transform rotation
    bool checkPlayer = true;

    // Set the elapsed time at the beginning of the game
    if (pat.statusTime == 0)
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();

    // Reset player id if the player is dead
    if (!masks[pat.focusEntity].has_value()) {
        setRandIdPlayer(pat, entityManager);
        return;
    }

    // limit cthulhu movement to the screen
    if (pos.x < 0)
        pos.x = 0;
    if (pos.x > _window->getSize().x - spriteAttribut.rect.width)
        pos.x = _window->getSize().x - spriteAttribut.rect.width;
    if (pos.y < 0)
        pos.y = 0;
    if (pos.y > _window->getSize().y - spriteAttribut.rect.height)
        pos.y = _window->getSize().y - spriteAttribut.rect.height;

    // Phase 2 Event
    if (life.life <= life.defaultLife / 2 && pat.phase == PHASE01) {
        pat.status = TypeStatus::TRANSFORM;
        pat.statusTime = this->_clock->getElapsedTime().asSeconds();
        pat.phase = PHASE02;
        pat.phaseCount = 4;
    }

    // Phase 1 && Phase 2 Attack && Phase 3 Rage Attack
    if (pat.phase == TypePhase::PHASE02) {
        if (pat.phaseCount == 0) {
            pat.phase = TypePhase::PHASE03;
            pat.phaseCount = 6;
        }
        delayIdle = 0;
    } else if (pat.phase == TypePhase::PHASE03) {
        if (pat.phaseCount == 0) {
            pat.phase = TypePhase::PHASE02;
            pat.phaseCount = 3;
        }
        delayIdle = 0;
    }

    // Pattern Status Part
    switch (pat.status) {
    case TypeStatus::SEARCH:
        pat.status = TypeStatus::IDLE;
        if (!this->setRandIdPlayer(pat, entityManager)) {
            pat.status = TypeStatus::SEARCH;
            checkPlayer = false;
        }
        if (pat.phase == TypePhase::PHASE01)
            pat.phaseCount = 1;
        vel.x = 0;
        vel.y = 0;
        break;

    case TypeStatus::IDLE:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayIdle) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::MOVE;
            if (checkPlayer)
                pat.lastPosFocus = componentManager.getSingleComponent<Position>(pat.focusEntity);
            if (pat.phase == TypePhase::PHASE01) {
                std::size_t soundId = entityManager.addMask((InfoComp::SOUNDID), componentManager);
                componentManager.getComponent(typeid(SoundID)).emplaceData(soundId, SoundID{2, false, false, 1});
            } else if (pat.phase == PHASE02) {
                pat.status = TypeStatus::MOVE;
                pat.phaseCount--;
            } else if (pat.phase == PHASE03) {
                pat.status = TypeStatus::ATTACK;
                pat.phaseCount--;
                std::size_t soundId = entityManager.addMask((InfoComp::SOUNDID), componentManager);
                componentManager.getComponent(typeid(SoundID)).emplaceData(soundId, SoundID{3, false, false, 1});
            }
        }
        if (checkPlayer) {
            posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
            vel.x = ((posPlayer.x - 20) - pos.x) / 500;
            vel.y = ((posPlayer.y - 20) - pos.y) / 500;
        } else {
            vel.x = 0;
            vel.y = 0;
        }
        break;

    case TypeStatus::MOVE:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayMove) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            if (pat.phase == TypePhase::PHASE01) {
                pat.angle = std::atan2(posPlayer.y - pos.y, posPlayer.x - pos.x);
                pat.status = TypeStatus::SHOOT;
                if (pat.phaseCount == 0)
                    pat.status = TypeStatus::SEARCH;
            } else {
                pat.status = TypeStatus::IDLE;
            }
        }
        if (checkPlayer) {
            posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
            if (pat.phase == TypePhase::PHASE01) {
                vel.x = ((posPlayer.x - 20) - pos.x) / 60;
                vel.y = ((posPlayer.y - 20) - pos.y) / 60;
            } else {
                vel.x = ((posPlayer.x - 20) - pos.x) / 200;
                vel.y = ((posPlayer.y - 20) - pos.y) / 200;
            }
        }
        break;

    case TypeStatus::SHOOT:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayShoot) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::MOVE;
            pat.phaseCount--;
        }
        if (checkPlayer) {
            posPlayer = componentManager.getSingleComponent<Position>(pat.focusEntity);
            vel.x = ((posPlayer.x - pos.x) / 100) + (std::cos(pat.angle) * SPEED_OSC);
            vel.y = ((posPlayer.y - pos.y) / 100) + (std::sin(pat.angle) * SPEED_OSC);
        }
        if (clEnemy.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > clEnemy.lastShoot + clEnemy.shootDelay) {
            if (entityManager.hasMask(id, InfoComp::SYNCID) == false)
                break;
            std::size_t idPar = componentManager.getSingleComponent<SyncID>(id).id;
            ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, {1, (posPlayer.x - pos.x) / 35, (posPlayer.y - pos.y) / 35, spriteAttribut.rotation - 90, idPar, *this->_syncId, 0});
            *this->_syncId += 1;
            clEnemy.lastShoot = _clock->getElapsedTime().asSeconds();
        }
        break;

    case TypeStatus::ATTACK:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayAttack) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::SEARCH;
            if (pat.phaseCount == 0) {
                std::size_t soundId = entityManager.addMask((InfoComp::SOUNDID), componentManager);
                componentManager.getComponent(typeid(SoundID)).emplaceData(soundId, SoundID{2, false, false, 1});
            }
        }
        vel.x = ((pat.lastPosFocus.x) - pos.x) / 10;
        vel.y = ((pat.lastPosFocus.y) - pos.y) / 10;
        break;

    case TypeStatus::TRANSFORM:
        if (this->_clock->getElapsedTime().asSeconds() - pat.statusTime >= delayTransform) {
            pat.statusTime = this->_clock->getElapsedTime().asSeconds();
            pat.status = TypeStatus::SEARCH;
            spriteID = SpriteID{S_CTHULHU_MOUTH, Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 110, 0};
            spriteAttribut.rect = {0, 0, 110, 146};
            std::size_t soundId = entityManager.addMask((InfoComp::SOUNDID), componentManager);
            componentManager.getComponent(typeid(SoundID)).emplaceData(soundId, SoundID{2, false, false, 1});
        }
        checkPlayer = false;
        spriteAttribut.rotation += (this->_clock->getElapsedTime().asSeconds() - pat.statusTime) * 10;
        vel.x = 0;
        vel.y = 0;
        break;

    default:
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
        if (!masks[i].has_value() || (entityManager.hasMask(i, appear) && componentManager.getSingleComponent<Appearance>(i).app))
            continue;
        if (entityManager.hasMask(i, eneParent) && componentManager.getSingleComponent<Parent>(i).follow == true) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            Position &parentPos = componentManager.getSingleComponent<Position>(componentManager.getSingleComponent<Parent>(i).id);
            pos.x = parentPos.x;
            pos.y = parentPos.y;
            continue;
        }

        if (!entityManager.hasMask(i, enemyData))
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
        if (pat.type == TypePattern::DEVOUREROSC) {
            this->devourerPattern(i, componentManager, entityManager);
            continue;
        }
        if (entityManager.hasMask(i, cooldownEnemy)) {
            CooldownShoot &clEnemy = componentManager.getSingleComponent<CooldownShoot>(i);
            if (clEnemy.shootDelay > 0 && _clock->getElapsedTime().asSeconds() > clEnemy.lastShoot + clEnemy.shootDelay) {
                if (entityManager.hasMask(i, InfoComp::SYNCID) == false)
                    continue;
                std::size_t idPar = componentManager.getSingleComponent<SyncID>(i).id;
                ProjectilePreload::createShoot(entityManager, componentManager, _window->getSize(), _screenSize, {1, -15, 0, 0, idPar, *this->_syncId, 0});
                *this->_syncId += 1;
                clEnemy.lastShoot = _clock->getElapsedTime().asSeconds();
            }
        }
    }
}

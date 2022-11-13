#include "Engine.hpp"

using namespace eng;

Engine::Engine()
{
    this->_loader.loadLevel({"R-Type/Assets/Levels/Online", "R-Type/Assets/Levels/Solo"});
    this->_loader.loadSounds({"R-Type/Assets/Audio/Musics", "R-Type/Assets/Audio/Sounds"});
    this->_loader.loadSprites({"R-Type/Assets/Sprites/Bonuses", "R-Type/Assets/Sprites/Enemies", "R-Type/Assets/Sprites/Fireballs", "R-Type/Assets/Sprites/GUI", "R-Type/Assets/Sprites/Parallax", "R-Type/Assets/Sprites/Player"});
}

ECS &Engine::getECS()
{
    return this->_ecs;
}

Graphic &Engine::getGraphic()
{
    return this->_graphic;
}

Loader &Engine::getLoader()
{
    return this->_loader;
}

void Engine::updateSize(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size)
{
    std::size_t checkSize = (InfoComp::SIZE | InfoComp::SPRITEAT);

    if (entityManager.hasMask(i, checkSize)) {
        Size &sizeI = componentManager.getSingleComponent<Size>(i);
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
        sizeI.x = sizeI.x / lastSize.x * size.x;
        sizeI.y = sizeI.y / lastSize.y * size.y;
        spriteAt.scale.x = spriteAt.scale.x / lastSize.x * size.x;
        spriteAt.scale.y = spriteAt.scale.y / lastSize.y * size.y;
    }
}

void Engine::updateSpeed(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size)
{
    std::size_t checkSpeed = (InfoComp::VEL);

    if (entityManager.hasMask(i, checkSpeed)) {
        Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
        if (vel.baseSpeedX != 0) {
            vel.baseSpeedX = vel.baseSpeedX / lastSize.x * size.x;
            vel.baseSpeedY = vel.baseSpeedY / lastSize.y * size.y;
        } else {
            vel.x = vel.x / lastSize.x * size.x;
            vel.y = vel.y / lastSize.y * size.y;
        }
    }
}

void Engine::updatePos(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size)
{
    std::size_t checkPos = (InfoComp::POS);

    if (entityManager.hasMask(i, checkPos)) {
        Position &pos = componentManager.getSingleComponent<Position>(i);
        pos.x = pos.x / lastSize.x * size.x;
        pos.y = pos.y / lastSize.y * size.y;
    }
}

void Engine::updateParallax(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size)
{
    std::size_t checkParSize = (InfoComp::SPRITEAT | InfoComp::PARALLAX);

    if (entityManager.hasMask(i, checkParSize)) {
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
        spriteAt.scale.x = spriteAt.scale.x / lastSize.x * size.x;
        spriteAt.scale.y = spriteAt.scale.y / lastSize.y * size.y;
        spriteAt.offset.x = spriteAt.offset.x / lastSize.x * size.x;
        spriteAt.offset.y = spriteAt.offset.y / lastSize.y * size.y;
        spriteAt.delay.x = spriteAt.delay.x / lastSize.x * size.x;
        spriteAt.delay.y = spriteAt.delay.y / lastSize.y * size.y;
    }
}

void Engine::updateAppDis(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size)
{
    std::size_t checkApp = (InfoComp::APP);
    std::size_t checkdis = (InfoComp::DIS);

    if (entityManager.hasMask(i, checkApp)) {
        Appearance &app = componentManager.getSingleComponent<Appearance>(i);
        app.end = app.end / lastSize.y * size.y;
    }
    if (entityManager.hasMask(i, checkdis)) {
        Disappearance &dis = componentManager.getSingleComponent<Disappearance>(i);
        dis.end = dis.end / lastSize.y * size.y;
    }
}

void Engine::updateSizeWindowId(sf::Vector2f lastSize, std::size_t i)
{
    std::shared_ptr<sf::RenderWindow> window = this->_graphic.getWindow();
    EntityManager &entityManager = this->_ecs.getEntityManager();
    ComponentManager &componentManager = this->_ecs.getComponentManager();
    std::size_t checkText = (InfoComp::TEXT);
    sf::Vector2f size = {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
    std::size_t checkCooldownBar = (InfoComp::COOLDOWNBAR | InfoComp::POS);

    if (entityManager.hasMask(i, checkText)) {
        Text &text = componentManager.getSingleComponent<Text>(i);
        text.pos.x = text.pos.x / lastSize.x * size.x;
        text.pos.y = text.pos.y / lastSize.y * size.y;
        text.size = text.size / lastSize.y * size.y;
    }
    if (entityManager.hasMask(i, checkCooldownBar)) {
        Position &cb = componentManager.getSingleComponent<Position>(i);
        cb.y = static_cast<float>(this->_graphic.getWindow()->getSize().y) - 20;
        return;
    }
    this->updatePos(i, componentManager, entityManager, lastSize, size);
    this->updateSpeed(i, componentManager, entityManager, lastSize, size);
    this->updateParallax(i, componentManager, entityManager, lastSize, size);
    this->updateSize(i, componentManager, entityManager, lastSize, size);
    this->updateAppDis(i, componentManager, entityManager, lastSize, size);
}

void Engine::updateSizeWindow(sf::Vector2f lastSize)
{
    std::shared_ptr<sf::RenderWindow> window = this->_graphic.getWindow();
    EntityManager &entityManager = this->_ecs.getEntityManager();
    ComponentManager &componentManager = this->_ecs.getComponentManager();
    std::size_t checkText = (InfoComp::TEXT);
    sf::Vector2f size = {static_cast<float>(this->_graphic.getEvent()->size.width), static_cast<float>(this->_graphic.getEvent()->size.height)};
    std::size_t checkCooldownBar = (InfoComp::COOLDOWNBAR | InfoComp::POS);

    window->setView(sf::View(sf::FloatRect(0, 0, size.x, size.y)));
    for (std::size_t i = 0; i < entityManager.getMasks().size(); i++) {
        if (entityManager.hasMask(i, checkText)) {
            Text &text = componentManager.getSingleComponent<Text>(i);
            text.pos.x = text.pos.x / lastSize.x * size.x;
            text.pos.y = text.pos.y / lastSize.y * size.y;
            text.size = text.size / lastSize.y * size.y;
        }
        if (entityManager.hasMask(i, checkCooldownBar)) {
            Position &cb = componentManager.getSingleComponent<Position>(i);
            cb.y = static_cast<float>(this->_graphic.getWindow()->getSize().y) - 20;
            continue;
        }
        this->updatePos(i, componentManager, entityManager, lastSize, size);
        this->updateSpeed(i, componentManager, entityManager, lastSize, size);
        this->updateParallax(i, componentManager, entityManager, lastSize, size);
        this->updateSize(i, componentManager, entityManager, lastSize, size);
        this->updateAppDis(i, componentManager, entityManager, lastSize, size);
    }
}

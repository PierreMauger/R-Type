#include "Engine.hpp"

using namespace eng;

Engine::Engine()
{
    // this->_loader.loadSounds({"R-Type/Assets/Sound"});
    this->_loader.loadLevel({"R-Type/Assets/Levels"});
    this->_loader.loadSounds({"R-Type/Assets/Sound"});
    this->_loader.loadSprites({"R-Type/Assets/Sprites", "R-Type/Assets/Sprites/Parallax", "R-Type/Assets/Sprites/zDevourerOfGods", "R-Type/Assets/Sprites/CthulhuEye"});
    std::srand(10);
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

Input &Engine::getInput()
{
    return this->_input;
}

void Engine::updateSize(auto &masks, std::size_t i, ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkSize = (InfoComp::SIZE | InfoComp::SPRITEAT);

    if ((masks[i].value() & checkSize) == checkSize) {
        Size &size = componentManager.getSingleComponent<Size>(i);
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
        size.x = size.x / lastSize.x * this->_graphic.getEvent()->size.width;
        size.y = size.y / lastSize.y * this->_graphic.getEvent()->size.height;
        spriteAt.scale.x = spriteAt.scale.x / lastSize.x * this->_graphic.getEvent()->size.width;
        spriteAt.scale.y = spriteAt.scale.y / lastSize.y * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateSpeed(auto &masks, std::size_t i, ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkSpeed = (InfoComp::VEL);

    if ((masks[i].value() & checkSpeed) == checkSpeed) {
        Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
        if (vel.baseSpeedX != 0) {
            vel.baseSpeedX = vel.baseSpeedX / lastSize.x * this->_graphic.getEvent()->size.width;
            vel.baseSpeedY = vel.baseSpeedY / lastSize.y * this->_graphic.getEvent()->size.height;
        } else {
            vel.x = vel.x / lastSize.x * this->_graphic.getEvent()->size.width;
            vel.y = vel.y / lastSize.y * this->_graphic.getEvent()->size.height;
        }
    }
}

void Engine::updatePos(auto &masks, std::size_t i, ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkPos = (InfoComp::POS);

    if ((masks[i].value() & checkPos) == checkPos) {
        Position &pos = componentManager.getSingleComponent<Position>(i);
        pos.x = pos.x / lastSize.x * this->_graphic.getEvent()->size.width;
        pos.y = pos.y / lastSize.y * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateParallax(auto &masks, std::size_t i, ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkParSize = (InfoComp::SPRITEAT | InfoComp::PARALLAX);

    if ((masks[i].value() & checkParSize) == checkParSize) {
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
        spriteAt.scale.x = spriteAt.scale.x / lastSize.x * this->_graphic.getEvent()->size.width;
        spriteAt.scale.y = spriteAt.scale.y / lastSize.y * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateAppDis(auto &masks, std::size_t i, ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkApp = (InfoComp::APP);
    std::size_t checkdis = (InfoComp::DIS);

    if ((masks[i].value() & checkApp) == checkApp) {
        Appearance &app = componentManager.getSingleComponent<Appearance>(i);
        app.end = app.end / lastSize.y * this->_graphic.getEvent()->size.height;
    }
    if ((masks[i].value() & checkdis) == checkdis) {
        Disappearance &dis = componentManager.getSingleComponent<Disappearance>(i);
        dis.end = dis.end / lastSize.y * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateSizeWindow()
{
    std::shared_ptr<sf::RenderWindow> window = this->_graphic.getWindow();
    EntityManager &entityManager = this->_ecs.getEntityManager();
    ComponentManager &componentManager = this->_ecs.getComponentManager();
    auto &masks = entityManager.getMasks();
    std::size_t checkText = (InfoComp::TEXT);
    std::size_t checkCooldownBar = (InfoComp::COOLDOWNBAR | InfoComp::POS);
    sf::Vector2f lastSize = this->_graphic.getLastSize();

    window->setView(sf::View(sf::FloatRect(0, 0, this->_graphic.getEvent()->size.width, this->_graphic.getEvent()->size.height)));
    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkText) == checkText) {
            Text &text = componentManager.getSingleComponent<Text>(i);
            text.pos.x = text.pos.x / lastSize.x * this->_graphic.getEvent()->size.width;
            text.pos.y = text.pos.y / lastSize.y * this->_graphic.getEvent()->size.height;
        }
        if ((masks[i].value() & checkCooldownBar) == checkCooldownBar) {
            Position &cb = componentManager.getSingleComponent<Position>(i);
            cb.y = static_cast<float>(this->_graphic.getWindow()->getSize().y) - 20;
            continue;
        }
        this->updatePos(masks, i, componentManager, lastSize);
        this->updateSpeed(masks, i, componentManager, lastSize);
        this->updateParallax(masks, i, componentManager, lastSize);
        this->updateSize(masks, i, componentManager, lastSize);
        this->updateAppDis(masks, i, componentManager, lastSize);
    }
}

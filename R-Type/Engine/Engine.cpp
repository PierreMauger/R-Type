#include "Engine.hpp"

using namespace eng;

Engine::Engine()
{
    this->_loader.loadSounds({"R-Type/Assets/Sound"});
    this->_loader.loadSprites({"R-Type/Assets/Sprites", "R-Type/Assets/Sprites/Parallax"});
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

Network &Engine::getNetwork()
{
    return this->_network;
}

Input &Engine::getInput()
{
    return this->_input;
}

void Engine::updateSize(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkSize = (eng::InfoComp::SIZE | eng::InfoComp::SPRITEAT);

    if ((masks[i].value() & checkSize) == checkSize) {
        Size &size = componentManager.getSingleComponent<Size>(i);
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
        size.x = (size.x / lastSize.x) * this->_graphic.getEvent()->size.width;
        size.y = (size.y / lastSize.y) * this->_graphic.getEvent()->size.height;
        spriteAt.scale.x = (spriteAt.scale.x / lastSize.x) * this->_graphic.getEvent()->size.width;
        spriteAt.scale.y = (spriteAt.scale.y / lastSize.y) * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateSpeed(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkSpeed = (eng::InfoComp::VEL);

    if ((masks[i].value() & checkSpeed) == checkSpeed) {
        Velocity &vel = componentManager.getSingleComponent<Velocity>(i);
        if (vel.baseSpeedX != 0) {
            vel.baseSpeedX = (vel.baseSpeedX / lastSize.x) * this->_graphic.getEvent()->size.width;
            vel.baseSpeedY = (vel.baseSpeedY / lastSize.y) * this->_graphic.getEvent()->size.height;
        } else {
            vel.x = (vel.x / lastSize.x) * this->_graphic.getEvent()->size.width;
            vel.y = (vel.y / lastSize.y) * this->_graphic.getEvent()->size.height;
        }
    }
}

void Engine::updatePos(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkPos = (eng::InfoComp::POS);

    if ((masks[i].value() & checkPos) == checkPos) {
        Position &pos = componentManager.getSingleComponent<Position>(i);
        pos.x = (pos.x / lastSize.x) * this->_graphic.getEvent()->size.width;
        pos.y = (pos.y / lastSize.y) * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateParallax(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize)
{
    std::size_t checkParSize = (eng::InfoComp::SPRITEAT | eng::InfoComp::PARALLAX);

    if ((masks[i].value() & checkParSize) == checkParSize) {
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
        spriteAt.scale.x = (spriteAt.scale.x / lastSize.x) * this->_graphic.getEvent()->size.width;
        spriteAt.scale.y = (spriteAt.scale.y / lastSize.y) * this->_graphic.getEvent()->size.height;
    }
}

void Engine::updateSizeWindow()
{
    std::shared_ptr<sf::RenderWindow> window = this->_graphic.getWindow();
    eng::EntityManager &entityManager = this->_ecs.getEntityManager();
    eng::ComponentManager &componentManager = this->_ecs.getComponentManager();
    auto &masks = entityManager.getMasks();
    std::size_t checkText = (eng::InfoComp::TEXT);
    std::size_t checkCooldownBar = (eng::InfoComp::COOLDOWNBAR | eng::InfoComp::POS);
    sf::Vector2f lastSize = this->_graphic.getLastSize();

    window->setView(sf::View(sf::FloatRect(0, 0, this->_graphic.getEvent()->size.width, this->_graphic.getEvent()->size.height)));
    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkText) == checkText) {
            Text &text = componentManager.getSingleComponent<Text>(i);
            text.pos.x = (text.pos.x / lastSize.x) * this->_graphic.getEvent()->size.width;
            text.pos.y = (text.pos.y / lastSize.y) * this->_graphic.getEvent()->size.height;
            continue;
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
    }
}

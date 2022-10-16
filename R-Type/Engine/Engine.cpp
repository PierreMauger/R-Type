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

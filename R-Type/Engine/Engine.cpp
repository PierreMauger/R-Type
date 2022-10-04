#include "Engine.hpp"

using namespace eng;

Engine::Engine()
{
    // this->_loader.loadSounds()
    this->_loader.loadSprites({"R-Type/assets/Sprites", "R-Type/assets/Sprites/background_parallax"});
}

ECS &Engine::getECS()
{
    return this->_ecs;
}

Graphic &Engine::getGraphic()
{
    return this->_graphic;
}

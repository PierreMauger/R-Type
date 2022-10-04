#include "Engine.hpp"

using namespace eng;

Engine::Engine()
{
}

ECS &Engine::getECS()
{
    return this->_ecs;
}

Graphic &Engine::getGraphic()
{
    return this->_graphic;
}

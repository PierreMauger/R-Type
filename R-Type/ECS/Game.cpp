#include "Game.hpp"

using namespace ECS;

Game::Game()
{
    this->_entityManager = EntityManager();
    this->_componentManager = ComponentManager();
    this->_systemManager = SystemManager();
}

void Game::update()
{
    this->_systemManager.updateSystems(this->_componentManager, this->_entityManager);
}

EntityManager &Game::getEntityManager()
{
    return this->_entityManager;
}

ComponentManager &Game::getComponentManager()
{
    return this->_componentManager;
}

SystemManager &Game::getSystemManager()
{
    return this->_systemManager;
}

#include "Engine.hpp"

namespace ECS
{
    Engine::Engine()
    {
        this->_entityManager = EntityManager();
        this->_componentManager = ComponentManager();
        this->_systemManager = SystemManager();

        // this->_systemManager.addSystem(std::make_unique<>());
    }

    void Engine::run()
    {
        this->_systemManager.updateSystems(this->_componentManager);
    }
}

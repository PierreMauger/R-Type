#include "Engine.hpp"
#include "System/ModelIdSystem.hpp"
#include "System/PhysicsSystem.hpp"

namespace ECS
{
    Engine::Engine()
    {
        this->_entityManager = EntityManager();
        this->_componentManager = ComponentManager();
        this->_systemManager = SystemManager();

        // this->_systemManager.addSystem(std::make_shared<>());
    }

    void Engine::run()
    {
        this->_systemManager.updateSystems(this->_componentManager);
    }
}

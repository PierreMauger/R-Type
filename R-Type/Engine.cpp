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

        this->_componentManager.addComponent(typeid(Position), {});
        this->_componentManager.addComponent(typeid(Velocity), {});
        this->_componentManager.addComponent(typeid(ModelID), {});

        this->_systemManager.addSystem(std::make_shared<ModelIdSystem>());
        this->_systemManager.addSystem(std::make_shared<PhysicsSystem>());
    }

    void Engine::run()
    {
        // while (true) {
            this->_systemManager.updateSystems(this->_componentManager);
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // }
    }
}

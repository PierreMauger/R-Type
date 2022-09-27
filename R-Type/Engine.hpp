#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Component/ComponentManager.hpp"
#include "Entity/EntityManager.hpp"
#include "System/RenderSystem.hpp"
#include "System/PhysicSystem.hpp"
#include "System/SystemManager.hpp"

namespace ECS
{
    class Engine
    {
        private:
            EntityManager _entityManager;
            ComponentManager _componentManager;
            SystemManager _systemManager;

        public:
            Engine();
            ~Engine() = default;
            EntityManager &getEntityManager();
            ComponentManager &getComponentManager();
            SystemManager &getSystemManager();

            void run();
    };
}

#endif // ENGINE_HPP

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "ECS/Component/ComponentManager.hpp"
#include "ECS/System/Physic/PhysicSystem.hpp"
#include "ECS/System/Render/RenderSystem.hpp"
#include "ECS/System/SystemManager.hpp"
#include "Entity/EntityManager.hpp"

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

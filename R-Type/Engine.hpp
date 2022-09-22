#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "Includes.hpp"
#include "SystemManager.hpp"

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

            void run();
    };
}

#endif // ENGINE_HPP
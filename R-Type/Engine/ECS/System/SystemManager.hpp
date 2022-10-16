#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class SystemManager
    {
        private:
            std::vector<std::shared_ptr<ISystem>> _systems;

        public:
            SystemManager();
            ~SystemManager();

            void addSystem(std::shared_ptr<ISystem> system);
            void updateSystems(ComponentManager &componentManager, EntityManager &entityManager);
            std::vector<std::shared_ptr<ISystem>> &getSystems();
    };
}

#endif // SYSTEMMANAGER_HPP

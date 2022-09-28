#ifndef GAME_HPP
#define GAME_HPP

#include "Component/ComponentManager.hpp"
#include "Entity/EntityManager.hpp"
#include "System/Physic/PhysicSystem.hpp"
#include "System/Render/RenderSystem.hpp"
#include "System/SystemManager.hpp"

namespace ECS
{
    class Game
    {
        private:
            EntityManager _entityManager;
            ComponentManager _componentManager;
            SystemManager _systemManager;

        public:
            Game();
            ~Game() = default;
            EntityManager &getEntityManager();
            ComponentManager &getComponentManager();
            SystemManager &getSystemManager();

            void update();
    };
}

#endif // GAME_HPP

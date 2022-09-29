#ifndef GAME_HPP
#define GAME_HPP

#include "ECS/Component/ComponentManager.hpp"
#include "Entity/EntityManager.hpp"
#include "ECS/System/Physic/PhysicSystem.hpp"
#include "ECS/System/Render/RenderSystem.hpp"
#include "ECS/System/SystemManager.hpp"

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

#ifndef ECS_HPP
#define ECS_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/ECS/System/Animation/AnimationSystem.hpp"
#include "Engine/ECS/System/Enemy/EnemySystem.hpp"
#include "Engine/ECS/System/GUI/GUISystem.hpp"
#include "Engine/ECS/System/Input/InputSystem.hpp"
// #include "Engine/ECS/System/Click/ClickSystem.hpp"
#include "Engine/ECS/System/Physic/PhysicSystem.hpp"
#include "Engine/ECS/System/Render/RenderSystem.hpp"
#include "Engine/ECS/System/Score/ScoreSystem.hpp"
#include "Engine/ECS/System/Sound/SoundSystem.hpp"
#include "Engine/ECS/System/SystemManager.hpp"

namespace eng
{
    class ECS
    {
        private:
            EntityManager _entityManager;
            ComponentManager _componentManager;
            SystemManager _systemManager;

        public:
            ECS();
            ~ECS() = default;

            EntityManager &getEntityManager();
            ComponentManager &getComponentManager();
            SystemManager &getSystemManager();

            void update();
    };
}

#endif // ECS_HPP

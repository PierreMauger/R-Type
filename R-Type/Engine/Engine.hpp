#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Engine/ECS/ECS.hpp"
#include "Engine/Graphic/Graphic.hpp"

namespace eng
{
    class Engine
    {
        private:
            ECS _ecs;
            Graphic _graphic;

        public:
            Engine();
            ~Engine() = default;

            ECS &getECS();
            Graphic &getGraphic();
    };
}

#endif // ENGINE_HPP

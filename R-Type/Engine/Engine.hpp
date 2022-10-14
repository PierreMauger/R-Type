#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Engine/ECS/ECS.hpp"
#include "Engine/Graphic/Graphic.hpp"
#include "Engine/Loader/Loader.hpp"
#include "Engine/Network/Network.hpp"

namespace eng
{
    class Engine
    {
        private:
            Loader _loader;
            ECS _ecs;
            Graphic _graphic;
            Network _network;

        public:
            Engine();
            ~Engine() = default;

            ECS &getECS();
            Graphic &getGraphic();
            Loader &getLoader();
            Network &getNetwork();
    };
}

#endif // ENGINE_HPP

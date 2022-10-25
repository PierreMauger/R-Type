#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Engine/ECS/ECS.hpp"
#include "Engine/Graphic/Graphic.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Loader/Loader.hpp"

namespace eng
{
    class Engine
    {
        private:
            Loader _loader;
            ECS _ecs;
            Graphic _graphic;
            Input _input;

            void updateSize(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize);
            void updateSpeed(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize);
            void updatePos(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize);
            void updateParallax(auto &masks, std::size_t i, eng::ComponentManager &componentManager, sf::Vector2f lastSize);

        public:
            Engine();
            ~Engine() = default;

            ECS &getECS();
            Graphic &getGraphic();
            Loader &getLoader();
            Input &getInput();
            void updateSizeWindow();
    };
}

#endif // ENGINE_HPP

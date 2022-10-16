/**
 * @file Engine.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The engine of the game containing the ECS, the graphics and the loader.
 * @copyright Epitech Rennes 2022
*/

#ifndef ENGINE_HPP
#define ENGINE_HPP

/// @cond
#include "Engine/ECS/ECS.hpp"
#include "Engine/Graphic/Graphic.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Loader/Loader.hpp"
#include "Engine/Network/Network.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The engine of the game containing the ECS, the graphics and the loader.
     * @class Engine
    */
    class Engine
    {
        private:
            Loader _loader;
            ECS _ecs;
            Graphic _graphic;
            Network _network;
            Input _input;

        public:
            /**
             * @brief Engine constructor.
             * @fn Engine()
            */
            Engine();
            /**
             * @brief Engine destructor.
             * @fn ~Engine()
            */
            ~Engine() = default;

            /**
             * @brief Get a reference to the engine's ECS.
             * @fn ECS &getECS()
             * @return A reference to the ECS
            */
            ECS &getECS();
            /**
             * @brief Get a reference to the engine's graphics.
             * @fn Graphic &getGraphic()
             * @return A reference to the graphics
            */
            Graphic &getGraphic();
            /**
             * @brief Get a reference to the engine's loader.
             * @fn Loader &getLoader()
             * @return A reference to the loader
            */
            Loader &getLoader();
            Network &getNetwork();
            Input &getInput();
    };
}

#endif // ENGINE_HPP

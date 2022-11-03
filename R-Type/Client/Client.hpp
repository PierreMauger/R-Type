/**
 * @file Client.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The client handling functions.
 * @copyright Epitech Rennes 2022
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

/// @cond
#include "ClientNetwork.hpp"
#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/MenuPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The client handling functions.
     * @class Client
     */
    class Client
    {
        private:
            Engine _engine;
            ClientNetwork _network;

            void initSystems();
            void initComponents();
            void initEntities();

        public:
            /**
             * @brief Client constructor
             * @fn Client(std::string ip, uint16_t portTcp)
             * @param ip The ip of the client
             * @param portTcp The tcp port of the client
             */
            Client(std::string ip, uint16_t portTcp);
            /**
             * @brief Client destructor
             * @fn ~Client()
             */
            ~Client() = default;

            /**
             * @brief Main loop of the client
             * @fn void mainLoop()
             */
            void mainLoop();
    };
}

#endif // CLIENT_HPP

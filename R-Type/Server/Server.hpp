/**
 * @file Server.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The server.
 * @copyright Epitech Rennes 2022
 */

#ifndef SERVER_HPP
#define SERVER_HPP

/// @cond
#include "Client.hpp"
#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/MenuPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "Engine/Network/Room.hpp"
#include "Includes.hpp"
#include "ServerGameSerializer.hpp"
#include "ServerMenuSerializer.hpp"
#include "ServerNetwork.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The engine of the game containing the ECS, the graphics and the loader.
     * @class Server
     */
    class Server
    {
        private:
            Engine _engine;
            ServerNetwork _network;

            ServerMenuSerializer _menuSerializer;
            ServerGameSerializer _gameSerializer;

            std::vector<Client> _clients;

            std::size_t _roomCount = 0;
            std::vector<Room> _rooms;

            sf::Time _elapsedTime = sf::seconds(0);
            sf::Time _deltaTime = sf::seconds(5);
            sf::Time _bossTime = sf::seconds(5);

            void initSystems();
            void initComponents();
            void initEntities();
            void manageEvent();
            void manageEnemy();
            void updateClients();

        public:
            /**
             * @brief Server constructor.
             * @fn Server()
             * @param portTcp The tcp port of the server
             */
            Server(uint16_t portTcp);
            /**
             * @brief Server destructor.
             * @fn ~Server()
             */
            ~Server() = default;

            /**
             * @brief The main server loop
             * @fn void mainLoop()
             */
            void mainLoop();
    };
}

#endif // SERVER_HPP

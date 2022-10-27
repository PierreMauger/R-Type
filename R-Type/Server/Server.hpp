#ifndef SERVER_HPP
#define SERVER_HPP

#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Includes.hpp"
#include "Room.hpp"
#include "ServerNetwork.hpp"

namespace eng
{
    class Server
    {
        private:
            Engine _engine;
            ServerNetwork _network;

            std::vector<Room> _rooms;
            sf::Time _elapsedTime = sf::seconds(0);
            sf::Time _deltaTime = sf::seconds(6);
            sf::Time _bossTime = sf::seconds(30);

            void initSystems();
            void initComponents();
            void initEntities();
            void manageEvent();
            void manageEnemy();

        public:
            Server(uint16_t portTcp);
            ~Server() = default;

            void mainLoop();
    };
}

#endif // SERVER_HPP

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Includes.hpp"
#include "ServerNetwork.hpp"

namespace eng
{
    class Server
    {
        private:
            Engine _engine;
            ServerNetwork _network;

            // std::vector

            void initSystems();
            void initComponents();
            void initEntities();

        public:
            Server(uint16_t portUdp, uint16_t portTcp);
            ~Server() = default;

            void mainLoop();
    };
}

#endif // SERVER_HPP

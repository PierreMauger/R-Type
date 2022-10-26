#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ClientNetwork.hpp"
#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Includes.hpp"

namespace eng
{
    class Client
    {
        private:
            Engine _engine;
            ClientNetwork _network;

            void initSystems();
            void initComponents();
            void initEntities();

        public:
            Client(std::string ip, uint16_t portTcp);
            ~Client() = default;

            void mainLoop();
    };
}

#endif // CLIENT_HPP

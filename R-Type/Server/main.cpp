#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"
#include "Network/Server/Server.hpp"
#include "Network/Connection.hpp"

// void updatePlayers(eng::Engine &engine, std::map<size_t, boost::shared_ptr<eng::Connection>> &players)
// {
//     std::vector<boost::shared_ptr<eng::Connection>> &listConnections = engine.getNetwork().getServer()->getConnections();
//     eng::ComponentManager &componentManager = engine.getECS().getComponentManager();
//     eng::VesselPreload vesselPreload;
//     size_t tmpId = 0;

//     if (listConnections.size() > players.size()) {
//         for (auto &player : players) {
//             if (player)
//         }
//         players.emplace()
//     }
// }

void mainLoop(eng::Engine &engine)
{
    eng::Graphic &graphic = engine.getGraphic();
    eng::ECS &ecs = engine.getECS();
    sf::Time elapsed_time = sf::seconds(0);
    sf::Time delta_time = sf::seconds(2);
    sf::Time boss_time = sf::seconds(20);
    eng::EnemyPreload enemyPreload;
    eng::BossPreload bossPreload;
    _QUEUE_TYPE &queueIn = engine.getNetwork().getServer()->getQueueIn();
    std::map<size_t, boost::shared_ptr<eng::Connection>> players;
    size_t refreshTick = 5;
    // eng::VesselPreload playerVessel;

    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
        }
        for (size_t count = 0; count < refreshTick; count++) {
            if (!queueIn.empty()) {
                // dataConnectionCheck(queue.pop_front());
                _STORAGE_DATA data = queueIn.pop_front();
                std::cout << "Message: " << data.data() << std::endl;
            } else {
                break;
            }
        }
        engine.getNetwork().getServer()->updateConnection();
        // if (graphic.getClock()->getElapsedTime() > boss_time) {
            // bossPreload.preload(engine);
            // boss_time = sf::seconds(boss_time.asSeconds() + 20);
        // } else if (graphic.getClock()->getElapsedTime() > elapsed_time) {
            // enemyPreload.preload(engine);
            // elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        // }
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./R-Type [PORT UDP] [PORT TCP]" << std::endl;
        return 1;
    }

    eng::Engine engine;
    eng::SystemManager &systemManager = engine.getECS().getSystemManager();
    eng::ComponentManager &componentManager = engine.getECS().getComponentManager();
    eng::Graphic &graphic = engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(engine.getLoader().getSprites());
    eng::Network &network = engine.getNetwork();

    // Setup Server
    network.initServer(std::stoi(av[1]), std::stoi(av[2]));

    // setup system & component
    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic.getEvent(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>());

    componentManager.bindComponent<Position>();
    componentManager.bindComponent<Velocity>();
    componentManager.bindComponent<Size>();
    componentManager.bindComponent<SpriteID>();
    componentManager.bindComponent<Controllable>();
    componentManager.bindComponent<Parallax>();
    componentManager.bindComponent<Projectile>();
    componentManager.bindComponent<Life>();
    componentManager.bindComponent<Enemy>();
    componentManager.bindComponent<Appearance>();
    componentManager.bindComponent<CooldownShoot>();
    componentManager.bindComponent<CooldownBar>();
    componentManager.bindComponent<LifeBar>();
    componentManager.bindComponent<Parent>();
    componentManager.bindComponent<Patern>();
    componentManager.bindComponent<DropBonus>();
    componentManager.bindComponent<Text>();

    // create background
    eng::ParallaxPreload parallaxPreload;
    parallaxPreload.preload(engine);

    network.getServer()->run();
    mainLoop(engine);
    return 0;
}
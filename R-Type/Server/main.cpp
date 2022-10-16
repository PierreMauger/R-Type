#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"
#include "Network/Server/Server.hpp"

void mainLoop(eng::Engine &engine)
{
    eng::Graphic &graphic = engine.getGraphic();
    eng::ECS &ecs = engine.getECS();
    sf::Time elapsed_time = sf::seconds(0);
    sf::Time delta_time = sf::seconds(2);
    eng::EnemyPreload enemyPreload;
    eng::BossPreload bossPreload;
    _QUEUE_TYPE &queue = engine.getNetwork().getServer()->getQueue();
    size_t refreshTick = 5;

    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
        }
        for (size_t count = 0; count < refreshTick; count++) {
            if (!queue.empty()) {
                _STORAGE_DATA data = queue.pop_front();
                std::cout << "Message: " << data.data() << std::endl;
            } else {
                break;
            }
        }
        // if (graphic.getClock()->getElapsedTime() > elapsed_time && graphic.getClock()->getElapsedTime().asSeconds() < 10) {
        //     enemyPreload.preload(engine);
        //     elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        // } else if (graphic.getClock()->getElapsedTime() > elapsed_time && elapsed_time.asSeconds() != 0) {
        //     bossPreload.preload(engine);
        //     elapsed_time = sf::seconds(0);
        // }
        // graphic.getWindow()->clear(sf::Color::Black);
        // ecs.update();
        // graphic.getWindow()->display();
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
    eng::Network &network = engine.getNetwork();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(engine.getLoader().getSprites());

    // Setup Server
    network.initServer(std::stoi(av[1]), std::stoi(av[2]));

    // Setup system & component
    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic.getEvent(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>(graphic.getWindow(), sprites));

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

    // create background
    eng::ParallaxPreload parallaxPreload;
    parallaxPreload.preload(engine);

    // Start server + Main loop
    network.getServer()->run();
    mainLoop(engine);
    return 0;
}
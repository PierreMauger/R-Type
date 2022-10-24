#include "Component/ComponentManager.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"

bool findVessel(eng::EntityManager &entityManager, eng::ComponentManager &componentManager, std::size_t &death, std::size_t &kill)
{
    auto &masks = entityManager.getMasks();
    std::size_t checkCon = (eng::InfoComp::CONTROLLABLE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkCon) == checkCon) {
            kill = componentManager.getSingleComponent<Controllable>(i).kill;
            return true;
        }
    }
    death++;
    return false;
}

void mainLoop(eng::Engine &engine)
{
    eng::Network &network = engine.getNetwork();

    eng::Graphic &graphic = engine.getGraphic();
    eng::ECS &ecs = engine.getECS();
    eng::VesselPreload vesselPreload;
    std::size_t death = 0;
    std::size_t kill = 0;

    vesselPreload.preload(engine);
    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
#endif
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
            if (graphic.getEvent()->type == sf::Event::Resized) {
                engine.updateSizeWindow();
                graphic.setLastSize(sf::Vector2f(graphic.getEvent()->size.width, graphic.getEvent()->size.height));
            }
        }
        if (!findVessel(ecs.getEntityManager(), ecs.getComponentManager(), death, kill))
            vesselPreload.preloadScore(engine, kill, death);
        if (!network.getClient()->isConnected())
            graphic.getWindow()->close();
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./R-Type [ip] [portUdp] [portTcp]" << std::endl;
        return 84;
    }

    eng::Engine engine;
    eng::SystemManager &systemManager = engine.getECS().getSystemManager();
    eng::ComponentManager &componentManager = engine.getECS().getComponentManager();
    eng::Network &network = engine.getNetwork();
    eng::Graphic &graphic = engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(engine.getLoader().getSprites());
    std::shared_ptr<std::vector<sf::SoundBuffer>> sounds = std::make_shared<std::vector<sf::SoundBuffer>>(engine.getLoader().getSounds());

    network.initClient(av[1], std::stoi(av[2]), std::stoi(av[3]));

    // setup system & component
    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock(), graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::ClickSystem>(graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic.getEvent(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock(), graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>());
    systemManager.addSystem(std::make_shared<eng::SoundSystem>(graphic.getClock(), sounds));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
#endif

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
    componentManager.bindComponent<Disappearance>();
    componentManager.bindComponent<CooldownShoot>();
    componentManager.bindComponent<CooldownBar>();
    componentManager.bindComponent<LifeBar>();
    componentManager.bindComponent<Parent>();
    componentManager.bindComponent<Patern>();
    componentManager.bindComponent<SyncID>();
    componentManager.bindComponent<DropBonus>();
    componentManager.bindComponent<Text>();
    componentManager.bindComponent<SoundID>();
    componentManager.bindComponent<SpriteAttribut>();
    componentManager.bindComponent<Button>();

    // create background
    eng::ParallaxPreload parallaxPreload;

    parallaxPreload.preload(engine);

    eng::BackgroundMusicPreload backgroundMusicPreload;

    backgroundMusicPreload.preload(engine);

    eng::ScoreTextPreload scoreTextPreload;

    scoreTextPreload.preload(engine);

    network.getClient()->run();
    mainLoop(engine);
    return 0;
}

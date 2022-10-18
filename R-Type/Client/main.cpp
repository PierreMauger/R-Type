#include "Component/ComponentManager.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"

void mainLoop(eng::Engine &engine)
{
    eng::Graphic &graphic = engine.getGraphic();
    eng::ECS &ecs = engine.getECS();
    sf::Time elapsed_time = sf::seconds(0);
    sf::Time delta_time = sf::seconds(2);
    sf::Time boss_time = sf::seconds(20);
    eng::EnemyPreload enemyPreload;
    eng::BossPreload bossPreload;

    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
#endif
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
        }
        if (graphic.getClock()->getElapsedTime() > boss_time) {
            bossPreload.preload(engine);
            boss_time = sf::seconds(boss_time.asSeconds() + 20);
        } else if (graphic.getClock()->getElapsedTime() > elapsed_time) {
            enemyPreload.preload(engine);
            elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        }
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

int main(void)
{
    eng::Engine engine;
    eng::SystemManager &systemManager = engine.getECS().getSystemManager();
    eng::ComponentManager &componentManager = engine.getECS().getComponentManager();
    eng::Graphic &graphic = engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(engine.getLoader().getSprites());
    std::shared_ptr<std::vector<sf::SoundBuffer>> sounds = std::make_shared<std::vector<sf::SoundBuffer>>(engine.getLoader().getSounds());

    // setup system & component
    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic.getEvent(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
#endif
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>(graphic.getWindow(), sprites));
    systemManager.addSystem(std::make_shared<eng::SoundSystem>(graphic.getClock(), sounds));

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
    componentManager.bindComponent<SyncID>();
    componentManager.bindComponent<DropBonus>();
    componentManager.bindComponent<Text>();
    componentManager.bindComponent<SoundID>();

    // create background
    eng::ParallaxPreload parallaxPreload;

    parallaxPreload.preload(engine);

    // create spaceship
    eng::VesselPreload vesselPreload;

    vesselPreload.preload(engine);

    eng::BackgroundMusicPreload backgroundMusicPreload;

    backgroundMusicPreload.preload(engine);

    // mainLoop(engine);

    _STORAGE_DATA packet = engine.getNetwork().getSerializer().serializeEntity(5, eng::EntityType::UPDATE, engine.getECS().getComponentManager());
    // _STORAGE_DATA packet = engine.getNetwork().getSerializer().serializeInput(sf::Keyboard::Left);

    for (std::size_t i = 0; i < 70; i++) {
        std::cout << (int)packet[i] << std::endl;
    }

    engine.getNetwork().getSerializer().handlePacket(packet, 5, engine.getECS().getEntityManager(), engine.getECS().getComponentManager(), engine.getInput(),
                                                     engine.getGraphic().getClock());
    return 0;
}

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
    eng::EnemyPreload enemyPreload;
    eng::BossPreload bossPreload;

    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
        }
        if (graphic.getClock()->getElapsedTime() > elapsed_time && graphic.getClock()->getElapsedTime().asSeconds() < 10) {
            enemyPreload.preload(engine);
            elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        } else if (graphic.getClock()->getElapsedTime() > elapsed_time && elapsed_time.asSeconds() != 0) {
            bossPreload.preload(engine);
            elapsed_time = sf::seconds(0);
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

    // setup system & component
    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), engine.getLoader()));
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock()));

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

    // create background
    eng::ParallaxPreload parallaxPreload;

    parallaxPreload.preload(engine);

    // create spaceship
    eng::VesselPreload vesselPreload;

    vesselPreload.preload(engine);

    // mainLoop(engine);
    std::vector<uint8_t> packet = engine.getNetwork().getUDPClient().getSerializer().serializeEntity(5, eng::EntityType::UPDATE, componentManager);

    // engine.getNetwork().getUDPClient().getSerializer().synchronizeEntity(packet, engine.getECS().getEntityManager(), componentManager);
    return 0;
}

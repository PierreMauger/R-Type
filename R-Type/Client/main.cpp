#include "Component/ComponentManager.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"

void mainLoop(eng::Engine &engine, std::shared_ptr<std::vector<sf::Sprite>> sprites)
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
            enemyPreload.preload(engine, sprites);
            elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        } else if (graphic.getClock()->getElapsedTime() > elapsed_time && elapsed_time.asSeconds() != 0) {
            bossPreload.preload(engine, sprites);
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
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(engine.getLoader().getSprites());

    // setup system & component
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
    componentManager.bindComponent<Text>();

    // create background
    eng::ParallaxPreload parallaxPreload;

    parallaxPreload.preload(engine, sprites);

    // create spaceship
    eng::VesselPreload vesselPreload;

    vesselPreload.preload(engine, sprites);

    mainLoop(engine, sprites);
    return 0;
}

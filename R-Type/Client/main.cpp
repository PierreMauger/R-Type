/**
 * @file main.cpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Main client file that initializes the engine with its systems, components and graphics then starts the main game loop.
 * @copyright Epitech Rennes 2022
 */

/// @cond
#include "Component/ComponentManager.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/BossPreload.hpp"
#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"
#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/Engine.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Main game loop running the R-Type.
 * @fn void mainLoop(eng::Engine &engine)
 * @param engine A reference to the engine containing the graphics and the ECS.
 */
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

/**
 * @brief Main function ran first when the r-type_client exectuable is launched.
 * @details Initializes the engine and the systems, components and graphics it'll contain then start the main loop.
 * @fn int main(void)
 */
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

    mainLoop(engine);
    return 0;
}

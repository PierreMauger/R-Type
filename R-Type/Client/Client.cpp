#include "Client.hpp"

eng::Client::Client(std::string ip, uint16_t portUdp, uint16_t portTcp) : _network(ip, portUdp, portTcp)
{
    this->initSystems();
    this->initComponents();
    this->initEntities();
}

void eng::Client::initSystems()
{
    eng::SystemManager &systemManager = this->_engine.getECS().getSystemManager();
    eng::Graphic &graphic = this->_engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(this->_engine.getLoader().getSprites());
    std::shared_ptr<std::vector<sf::SoundBuffer>> sounds = std::make_shared<std::vector<sf::SoundBuffer>>(this->_engine.getLoader().getSounds());

    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock(), graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow()));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic.getEvent(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
#endif
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock(), graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>());
    systemManager.addSystem(std::make_shared<eng::SoundSystem>(graphic.getClock(), sounds));
}

void eng::Client::initComponents()
{
    eng::ComponentManager &componentManager = this->_engine.getECS().getComponentManager();

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
}

void eng::Client::initEntities()
{
    eng::ParallaxPreload parallaxPreload;
    eng::BackgroundMusicPreload backgroundMusicPreload;
    eng::ScoreTextPreload scoreTextPreload;
    eng::VesselPreload vesselPreload;

    parallaxPreload.preload(this->_engine);
    backgroundMusicPreload.preload(this->_engine);
    scoreTextPreload.preload(this->_engine);
    vesselPreload.preload(this->_engine);
}

// TODO REMOVE THIS **
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

void eng::Client::mainLoop()
{
    eng::Graphic &graphic = this->_engine.getGraphic();
    eng::ECS &ecs = this->_engine.getECS();
    eng::VesselPreload vesselPreload;
    std::size_t death = 0;
    std::size_t kill = 0;

    this->_network.run();
    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
#endif
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
            if (graphic.getEvent()->type == sf::Event::Resized) {
                this->_engine.updateSizeWindow();
                graphic.setLastSize(sf::Vector2f(graphic.getEvent()->size.width, graphic.getEvent()->size.height));
            }
        }
        if (!findVessel(ecs.getEntityManager(), ecs.getComponentManager(), death, kill))
            vesselPreload.preloadScore(this->_engine, kill, death);
        if (!this->_network.isConnected())
            graphic.getWindow()->close();
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

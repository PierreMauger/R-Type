#include "Server.hpp"

eng::Server::Server(uint16_t portTcp) : _network(portTcp)
{
    this->initSystems();
    this->initComponents();
    this->initEntities();
}

// TODO see if graph is usefull on serv
void eng::Server::initSystems()
{
    eng::SystemManager &systemManager = this->_engine.getECS().getSystemManager();
    eng::Graphic &graphic = this->_engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(this->_engine.getLoader().getSprites());

    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic.getEvent(), graphic.getClock(), graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic.getEvent(), graphic.getClock(), sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic.getWindow(), graphic.getClock(), sprites, graphic.getScreenSize()));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic.getWindow()));
#endif
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic.getClock(), graphic.getWindow(), graphic.getScreenSize()));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>());
}

void eng::Server::initComponents()
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

void eng::Server::initEntities()
{
    eng::ParallaxPreload parallaxPreload;
    eng::ScoreTextPreload scoreTextPreload;

    parallaxPreload.preload(this->_engine);
    scoreTextPreload.preload(this->_engine);
}

// TODO make do separated function
void eng::Server::mainLoop()
{
    _QUEUE_TYPE &dataIn = this->_network.getQueueIn();
    std::size_t refreshTick = 5;
    std::map<std::string, boost::shared_ptr<eng::Connection>> players;

    eng::Graphic &graphic = this->_engine.getGraphic();
    eng::ECS &ecs = this->_engine.getECS();
    sf::Time elapsed_time = sf::seconds(0);
    sf::Time delta_time = sf::seconds(6);
    sf::Time boss_time = sf::seconds(30);
    eng::EnemyPreload enemyPreload;
    eng::BossPreload bossPreload;
    eng::VesselPreload vesselPreload;

    vesselPreload.preload(this->_engine);
    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
#ifndef NDEBUG
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
#endif
            if (graphic.getEvent()->type == sf::Event::Closed)
                graphic.getWindow()->close();
            if (graphic.getEvent()->type == sf::Event::Resized) {
                this->_engine.updateSizeWindow();
                graphic.setLastSize(sf::Vector2f(graphic.getEvent()->size.width, graphic.getEvent()->size.height));
            }
        }
        if (graphic.getClock()->getElapsedTime() > boss_time) {
            bossPreload.preload(this->_engine);
            boss_time = sf::seconds(boss_time.asSeconds() + 30);
        } else if (graphic.getClock()->getElapsedTime() > elapsed_time) {
            enemyPreload.preload(this->_engine);
            elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        }
        for (size_t count = 0; count < refreshTick; count++) {
            if (!dataIn.empty()) {
                std::cout << "Message: " << dataIn.pop_front().data() << std::endl;
            } else {
                break;
            }
        }
        this->_network.updateConnection();
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

#include "Server.hpp"

using namespace eng;

Server::Server(uint16_t portTcp) : _network(portTcp)
{
    this->initSystems();
    this->initComponents();
    this->initEntities();
    this->_network.run();
}

// TODO see if graph is usefull on serv
void Server::initSystems()
{
    SystemManager &systemManager = this->_engine.getECS().getSystemManager();
    EntityManager &entityManager = this->_engine.getECS().getEntityManager();
    Graphic &graphic = this->_engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(this->_engine.getLoader().getSprites());

    systemManager.addSystem(std::make_shared<InputSystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<PhysicSystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<AnimationSystem>(graphic, entityManager, sprites));
    systemManager.addSystem(std::make_shared<RenderSystem>(graphic, entityManager, sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<GUISystem>(graphic));
#endif
    systemManager.addSystem(std::make_shared<EnemySystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<ScoreSystem>(entityManager));
    systemManager.addSystem(std::make_shared<ClickSystem>(graphic, entityManager));
}

void Server::initComponents()
{
    ComponentManager &componentManager = this->_engine.getECS().getComponentManager();

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
    componentManager.bindComponent<Pattern>();
    componentManager.bindComponent<SyncID>();
    componentManager.bindComponent<DropBonus>();
    componentManager.bindComponent<Text>();
    componentManager.bindComponent<SoundID>();
    componentManager.bindComponent<SpriteAttribut>();
    componentManager.bindComponent<GroupEntity>();
    componentManager.bindComponent<Button>();
}

void Server::initEntities()
{
    ParallaxPreload::preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    ScoreTextPreload::preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    MenuPreload::preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
}

void Server::manageEvent()
{
    Graphic &graphic = this->_engine.getGraphic();

    while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
#ifndef NDEBUG
        ImGui::SFML::ProcessEvent(*graphic.getEvent());
#endif
        if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            graphic.getWindow()->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && !graphic.isFullscreen()) {
            graphic.getWindow()->create(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Fullscreen);
            graphic.getWindow()->setFramerateLimit(60);
            graphic.setFullscreen(true);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && graphic.isFullscreen()) {
            graphic.getWindow()->create(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Default);
            graphic.getWindow()->setFramerateLimit(60);
            graphic.setFullscreen(false);
        }
        if (graphic.getEvent()->type == sf::Event::Resized) {
            this->_engine.updateSizeWindow();
            graphic.setLastSize(sf::Vector2f(graphic.getEvent()->size.width, graphic.getEvent()->size.height));
        }
    }
}

void Server::manageEnemy()
{
    eng::Graphic &graphic = this->_engine.getGraphic();

    if (graphic.getClock()->getElapsedTime() > this->_bossTime) {
        BossPreload::preload(graphic, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        this->_bossTime = sf::seconds(this->_bossTime.asSeconds() + 30);
    } else if (graphic.getClock()->getElapsedTime() > this->_elapsedTime) {
        EnemyPreload::preload(graphic, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        this->_elapsedTime = graphic.getClock()->getElapsedTime() + this->_deltaTime;
    }
}

// TODO make do separated function
void Server::mainLoop()
{
    _QUEUE_TYPE &dataIn = this->_network.getQueueIn();
    std::size_t refreshTick = 5;
    std::map<std::string, boost::shared_ptr<Connection>> players;

    Graphic &graphic = this->_engine.getGraphic();
    ECS &ecs = this->_engine.getECS();

    VesselPreload::preload(graphic, ecs.getEntityManager(), ecs.getComponentManager());
    DevourerPreload::preload(graphic, ecs.getEntityManager(), ecs.getComponentManager());
    while (graphic.getWindow()->isOpen()) {
        this->manageEvent();
        this->manageEnemy();
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

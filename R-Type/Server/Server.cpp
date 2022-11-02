#include "Server.hpp"

eng::Server::Server(uint16_t portTcp)
    : _network(portTcp)
{
    this->initSystems();
    this->initComponents();
    this->initEntities();
    this->_network.run();
}

// TODO see if graph is usefull on serv
void eng::Server::initSystems()
{
    eng::SystemManager &systemManager = this->_engine.getECS().getSystemManager();
    eng::EntityManager &entityManager = this->_engine.getECS().getEntityManager();
    eng::Graphic &graphic = this->_engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(this->_engine.getLoader().getSprites());

    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic, sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic, sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic));
#endif
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>());

    entityManager.addMaskCategory(InfoComp::TEXT);
    entityManager.addMaskCategory(InfoComp::POS | InfoComp::SPRITEID);
    entityManager.addMaskCategory(InfoComp::SOUNDID);
    entityManager.addMaskCategory(InfoComp::CONTROLLABLE);
    entityManager.addMaskCategory(InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);
    entityManager.addMaskCategory(InfoComp::SPRITEID | InfoComp::SPRITEAT);
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
    componentManager.bindComponent<Pattern>();
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

    parallaxPreload.preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    scoreTextPreload.preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
}

void eng::Server::manageEvent()
{
    eng::Graphic &graphic = this->_engine.getGraphic();

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

void eng::Server::manageEnemy()
{
    eng::Graphic &graphic = this->_engine.getGraphic();
    eng::EnemyPreload enemyPreload;
    eng::BossPreload bossPreload;

    if (graphic.getClock()->getElapsedTime() > this->_bossTime) {
        bossPreload.preload(graphic, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        this->_bossTime = sf::seconds(this->_bossTime.asSeconds() + 30);
    } else if (graphic.getClock()->getElapsedTime() > this->_elapsedTime) {
        enemyPreload.preload(graphic, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        this->_elapsedTime = graphic.getClock()->getElapsedTime() + this->_deltaTime;
    }
}

// TODO make do separated function
void eng::Server::mainLoop()
{
    _QUEUE_TYPE &dataIn = this->_network.getQueueIn();
    std::size_t refreshTick = 5;
    std::map<std::string, boost::shared_ptr<eng::Connection>> players;

    eng::Graphic &graphic = this->_engine.getGraphic();
    eng::ECS &ecs = this->_engine.getECS();
    eng::VesselPreload vesselPreload;
    eng::DevourerPreload devourerPreload;

    vesselPreload.preload(graphic, ecs.getEntityManager(), ecs.getComponentManager());
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

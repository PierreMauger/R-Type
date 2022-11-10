#include "Client.hpp"

using namespace eng;

Client::Client()
{
    this->_ip = std::make_shared<std::string>("127.0.0.1");
    this->_port = std::make_shared<std::size_t>(8080);
    this->_isLocal = std::make_shared<bool>(false);
    this->initSystems();
    this->initComponents();
    this->initEntities();
}

void Client::createNetwork()
{
    this->_network = std::make_shared<ClientNetwork>("127.0.0.1", 8080);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    this->_network->run();

    // this->_id = this->_network->getId();
    // std::srand(this->_network->getTime());
}

void Client::initSystems()
{
    SystemManager &systemManager = this->_engine.getECS().getSystemManager();
    EntityManager &entityManager = this->_engine.getECS().getEntityManager();
    Graphic &graphic = this->_engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(this->_engine.getLoader().getSprites());
    std::shared_ptr<std::vector<sf::SoundBuffer>> sounds = std::make_shared<std::vector<sf::SoundBuffer>>(this->_engine.getLoader().getSounds());

    systemManager.addSystem(std::make_shared<InputSystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<PhysicSystem>(graphic, entityManager, nullptr));
    systemManager.addSystem(std::make_shared<AnimationSystem>(graphic, entityManager, sprites));
    systemManager.addSystem(std::make_shared<RenderSystem>(graphic, entityManager, sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<GUISystem>(graphic));
#endif
    systemManager.addSystem(std::make_shared<EnemySystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<ScoreSystem>(entityManager));
    systemManager.addSystem(std::make_shared<SoundSystem>(graphic, entityManager, sounds));
    systemManager.addSystem(std::make_shared<ClickSystem>(graphic, this->_port, this->_ip, this->_isLocal, entityManager));
}

void Client::initComponents()
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
    componentManager.bindComponent<Button>();
    componentManager.bindComponent<Shield>();
    componentManager.bindComponent<Scene>();
}

void Client::initEntities()
{
    ParallaxPreload::preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    MenuPreload::preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
}

void Client::syncUdpNetwork()
{
    _QUEUE_TYPE &dataIn = this->_network->getQueueInUdp();
    _STORAGE_DATA packet;

    if (dataIn.empty())
        return;
    for (packet = dataIn.pop_front(); true; packet = dataIn.pop_front()) {
        this->_gameSerializer.handlePacket(packet, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        if (dataIn.empty())
            break;
    }
}

void Client::syncTcpNetwork()
{
    _QUEUE_TYPE &dataIn = this->_network->getQueueInTcp();
    _STORAGE_DATA packet;

    if (dataIn.empty())
        return;
    for (packet = dataIn.pop_front(); true; packet = dataIn.pop_front()) {
        this->_menuSerializer.handlePacket(packet, this->_rooms, this->_roomId);
        if (dataIn.empty())
            break;
    }
}

void Client::updateNetwork()
{
    if (this->_network == nullptr && this->_ip->size() != 0 && (*this->_port) != 0) {
        this->createNetwork();
        return;
    }

    Graphic &graphic = this->_engine.getGraphic();

    if (graphic.getClock()->getElapsedTime() <= this->_networkTime)
        return;
    this->_networkTime = graphic.getClock()->getElapsedTime() + sf::milliseconds(50);
    this->syncUdpNetwork();
    this->syncTcpNetwork();
    this->_network->updateConnection();
}

void Client::updateEvent()
{
    Graphic &graphic = this->_engine.getGraphic();

    while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
#ifndef NDEBUG
        ImGui::SFML::ProcessEvent(*graphic.getEvent());
#endif
        if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            graphic.getWindow()->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) {
            graphic.getWindow()->create(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Fullscreen - graphic.isFullscreen());
            graphic.getWindow()->setFramerateLimit(60);
            graphic.setFullscreen(!graphic.isFullscreen());
        }
        if (graphic.getEvent()->type == sf::Event::Resized) {
            this->_engine.updateSizeWindow();
            graphic.setLastSize(sf::Vector2f(graphic.getEvent()->size.width, graphic.getEvent()->size.height));
        }
    }
}

void Client::manageEnemy(Level &level, Graphic &graphic, ECS &ecs)
{
    std::size_t i = 0;

    if (graphic.getClock()->getElapsedTime().asSeconds() > (level.getDelayRead() + level.getSpeedRead()) || level.getDelayRead() == 0) {
        level.parseLevel(graphic, ecs.getEntityManager(), ecs.getComponentManager(), i);
        level.setDelayRead(graphic.getClock()->getElapsedTime().asSeconds());
    }
}

void Client::mainLoop()
{
    Graphic &graphic = this->_engine.getGraphic();
    ECS &ecs = this->_engine.getECS();
    std::vector<Level> &level = this->_engine.getLoader().getLevels();

    std::size_t i = 0;
    while (graphic.getWindow()->isOpen()) {
        this->updateEvent();
        if (*this->_isLocal)
            this->manageEnemy(level[0], graphic, ecs);
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
        this->updateNetwork();
    }
}

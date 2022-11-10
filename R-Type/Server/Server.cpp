#include "Server.hpp"

using namespace eng;

Server::Server(uint16_t portTcp, time_t time) : _network(portTcp, time)
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
    std::shared_ptr<std::vector<sf::SoundBuffer>> sounds = std::make_shared<std::vector<sf::SoundBuffer>>(this->_engine.getLoader().getSounds());

    systemManager.addSystem(std::make_shared<InputSystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<PhysicSystem>(graphic, entityManager, std::make_shared<std::size_t>(this->_syncId)));
    systemManager.addSystem(std::make_shared<AnimationSystem>(graphic, entityManager, sprites));
    systemManager.addSystem(std::make_shared<RenderSystem>(graphic, entityManager, sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<GUISystem>(graphic));
#endif
    systemManager.addSystem(std::make_shared<EnemySystem>(graphic, entityManager));
    systemManager.addSystem(std::make_shared<ScoreSystem>(entityManager));
    systemManager.addSystem(std::make_shared<SoundSystem>(graphic, entityManager, sounds));
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
    componentManager.bindComponent<Button>();
    componentManager.bindComponent<Shield>();
    componentManager.bindComponent<Scene>();
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

void Server::manageEnemy(Level &level, Graphic &graphic, ECS &ecs)
{
    if (graphic.getClock()->getElapsedTime().asSeconds() > (level.getDelayRead() + level.getSpeedRead()) || level.getDelayRead() == 0) {
        level.parseLevel(graphic, ecs.getEntityManager(), ecs.getComponentManager(), this->_syncId);
        level.setDelayRead(graphic.getClock()->getElapsedTime().asSeconds());
    }
}

void Server::syncUdpNetwork(Client &client)
{
    _QUEUE_TYPE &dataIn = this->_network.getQueueInUdp();
    _STORAGE_DATA packet;

    if (dataIn.empty())
        return;
    for (packet = dataIn.pop_front(); true; packet = dataIn.pop_front()) {
        this->_gameSerializer.handlePacket(packet, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager(), client);
        if (dataIn.empty())
            break;
    }
}

void Server::syncTcpNetwork(Client &client)
{
    _QUEUE_TYPE &dataIn = this->_network.getQueueInTcp();
    _STORAGE_DATA packet;

    if (dataIn.empty())
        return;
    for (packet = dataIn.pop_front(); true; packet = dataIn.pop_front()) {
        this->_menuSerializer.handlePacket(packet, this->_rooms, client, this->_roomId);
        if (dataIn.empty())
            break;
    }
}

void Server::updateRooms()
{
    for (auto &room : this->_rooms) {
        if (room.isFull() && !room.isStarted()) {
            room.start();
            auto packet = this->_menuSerializer.serializeEvent(MenuEvent::GAME_START);
            this->_network.tcpMsgRoom(packet, room.getId(), this->_clients);
        }
        if (room.getNbPlayers() == 0) {
            this->_rooms.erase(std::remove(this->_rooms.begin(), this->_rooms.end(), room), this->_rooms.end());
        }
    }
}

void Server::updateClients()
{
    bool check = false;
    std::vector<std::shared_ptr<Connection>> &connections = this->_network.getConnections();

    if (this->_clients.size() == connections.size())
        return;
    for (auto &connection : connections) {
        for (auto &client : this->_clients) {
            if (client.getConnection() == connection)
                check = true;
        }
        if (!check) {
            this->_clients.push_back(Client(connection, this->_roomId++));
        }
        check = false;
    }
    for (auto &client : this->_clients) {
        if (!client.getConnection()->isConnected()) {
            client.destroyClient(this->_rooms, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
            this->_clients.erase(std::remove(this->_clients.begin(), this->_clients.end(), client), this->_clients.end());
        }
    }
}

void Server::updateEntities()
{
    EntityManager &entityManager = this->_engine.getECS().getEntityManager();
    ComponentManager &componentManager = this->_engine.getECS().getComponentManager();
    auto &masks = entityManager.getMasks();

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & InfoComp::SYNCID) == InfoComp::SYNCID) {
            _STORAGE_DATA packet = this->_gameSerializer.serializeEntity(i, CrudType::UPDATE, entityManager, componentManager);
            this->_network.udpMsgAll(packet);
        }
    }
}

void Server::updateNetwork()
{
    Graphic &graphic = this->_engine.getGraphic();

    // this->syncTcpNetwork();
    // this->syncUdpNetwork();
    if (graphic.getClock()->getElapsedTime() <= this->_networkTime)
        return;
    this->_networkTime = graphic.getClock()->getElapsedTime() + sf::milliseconds(50);
    this->updateClients();
    this->updateEntities();
    this->_network.updateConnection();
}

void Server::mainLoop()
{
    Graphic &graphic = this->_engine.getGraphic();
    ECS &ecs = this->_engine.getECS();
    std::vector<Level> &level = this->_engine.getLoader().getLevels();

    VesselPreload::preload(graphic.getWindow()->getSize(), graphic.getScreenSize(), ecs.getEntityManager(), ecs.getComponentManager(), this->_syncId);
    while (graphic.getWindow()->isOpen()) {
        this->manageEvent();
        this->manageEnemy(level[0], graphic, ecs);
        this->updateRooms();
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
        this->updateNetwork();
    }
}

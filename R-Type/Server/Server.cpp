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
    Graphic &graphic = this->_engine.getGraphic();

    if (graphic.getClock()->getElapsedTime() > this->_bossTime) {
        BossPreload::preload(graphic, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        this->_bossTime = sf::seconds(this->_bossTime.asSeconds() + 30);
    } else if (graphic.getClock()->getElapsedTime() > this->_elapsedTime) {
        EnemyPreload::preload(graphic, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        this->_elapsedTime = graphic.getClock()->getElapsedTime() + this->_deltaTime;
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
            this->_clients.push_back(Client(connection));
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
    this->updateClients();
    this->updateEntities();
    this->_network.updateConnection();
}

void Server::mainLoop()
{
    Graphic &graphic = this->_engine.getGraphic();
    ECS &ecs = this->_engine.getECS();

    VesselPreload::preload(graphic, ecs.getEntityManager(), ecs.getComponentManager());
    while (graphic.getWindow()->isOpen()) {
        this->manageEvent();
        this->manageEnemy();
        this->updateRooms();
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
        this->updateNetwork();
    }
}

#include "Client.hpp"

using namespace eng;

Client::Client()
{
    this->_ip = std::make_shared<std::string>("");
    this->_port = std::make_shared<std::size_t>(0);
    this->_isLocal = std::make_shared<bool>(false);
    this->_syncId = std::make_shared<std::size_t>(0);
    this->initSystems();
    this->initComponents();
    this->initEntities();
}

void Client::createNetwork()
{
    this->_network = std::make_shared<ClientNetwork>(*this->_ip, *this->_port);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_network->run();

    this->_id = this->_network->getId();
    std::srand(this->_network->getTime());
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
    systemManager.addSystem(std::make_shared<ClickSystem>(graphic, this->_port, this->_ip, this->_isLocal, this->_syncId, entityManager));
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
    ScoreTextPreload::preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
}

void Client::syncUdpNetwork()
{
    _QUEUE_TYPE &dataIn = this->_network->getQueueInUdp();

    if (dataIn.empty())
        return;
    for (_STORAGE_DATA packet = dataIn.pop_front(); true; packet = dataIn.pop_front()) {
        try {
            this->_gameSerializer.handlePacket(packet, this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        if (dataIn.empty())
            break;
    }
}

void Client::syncTcpNetwork()
{
    _QUEUE_TYPE &dataIn = this->_network->getQueueInTcp();

    if (dataIn.empty())
        return;
    for (_STORAGE_DATA packet = dataIn.pop_front(); true; packet = dataIn.pop_front()) {
        try {
            this->_menuSerializer.handlePacket(packet, this->_rooms, this->_roomId);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        if (dataIn.empty())
            break;
    }
}

void Client::updateNetwork()
{
    if (this->_network == nullptr) {
        if (this->_ip->size() == 0 || (*this->_port) == 0) {
            return;
        }
        this->createNetwork();
    }

    Graphic &graphic = this->_engine.getGraphic();

    if (graphic.getClock()->getElapsedTime() <= this->_networkTime)
        return;
    this->_networkTime = graphic.getClock()->getElapsedTime() + sf::milliseconds(16);
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

bool Client::checkIfEnemyAlive(EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic)
{
    auto &masks = entityManager.getMasks();
    bool textSpawn = false;
    bool isText = false;

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & InfoComp::ENEMY) == InfoComp::ENEMY)
            return false;
        if (masks[i].has_value() && (masks[i].value() & InfoComp::TEXT) == InfoComp::TEXT && componentManager.getSingleComponent<Text>(i).delay != 0) {
            isText = true;
            Text &text = componentManager.getSingleComponent<Text>(i);
            if (text.delay != 0 && text.last + text.delay < graphic.getClock()->getElapsedTime().asSeconds()) {
                textSpawn = true;
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
            }
        }
    }
    if (!isText) {
        ScoreTextPreload::levelPreload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
        BackgroundMusicPreload::preloadMusic(this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager(), 5);
    }
    return textSpawn;
}

bool Client::manageEnemy(Level &level, Graphic &graphic, ECS &ecs)
{
    if (this->_isLevelFinished) {
        if (this->checkIfEnemyAlive(ecs.getEntityManager(), ecs.getComponentManager(), graphic))
            return true;
    }
    if (graphic.getClock()->getElapsedTime().asSeconds() > (level.getDelayRead() + level.getSpeedRead()) || level.getDelayRead() == 0) {
        this->_isLevelFinished = level.parseLevel(graphic, ecs.getEntityManager(), ecs.getComponentManager(), *this->_syncId);
        level.setDelayRead(graphic.getClock()->getElapsedTime().asSeconds());
    }
    return false;
}

void Client::updateKeys()
{
    if (this->_network == nullptr) {
        if (this->_ip->size() == 0 || (*this->_port) == 0) {
            return;
        }
        this->createNetwork();
    }

    Graphic &graphic = this->_engine.getGraphic();

    if (graphic.getClock()->getElapsedTime() <= this->_keysTime)
        return;
    this->_keysTime = graphic.getClock()->getElapsedTime() + sf::milliseconds(16);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _STORAGE_DATA packet = this->_gameSerializer.serializeInput(this->_id, sf::Keyboard::Left);
        this->_network->udpMsg(packet);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _STORAGE_DATA packet = this->_gameSerializer.serializeInput(this->_id, sf::Keyboard::Right);
        this->_network->udpMsg(packet);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _STORAGE_DATA packet = this->_gameSerializer.serializeInput(this->_id, sf::Keyboard::Up);
        this->_network->udpMsg(packet);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _STORAGE_DATA packet = this->_gameSerializer.serializeInput(this->_id, sf::Keyboard::Down);
        this->_network->udpMsg(packet);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        _STORAGE_DATA packet = this->_gameSerializer.serializeInput(this->_id, sf::Keyboard::Enter);
        this->_network->udpMsg(packet);
    }
}

void Client::mainLoop()
{
    Graphic &graphic = this->_engine.getGraphic();
    ECS &ecs = this->_engine.getECS();
    std::vector<Level> &level = this->_engine.getLoader().getLevels();
    std::size_t levelId = 0;

    while (graphic.getWindow()->isOpen()) {
        this->updateEvent();
        if (*this->_isLocal) {
            if (this->manageEnemy(level[levelId], graphic, ecs)) {
                this->_isLevelFinished = false;
                if (level.size() - 1 == levelId)
                    graphic.getWindow()->close();
                else
                    levelId++;
            }
        }
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
        this->updateKeys();
        this->updateNetwork();
    }
}

#include "Client.hpp"

eng::Client::Client(std::string ip, uint16_t portTcp) : _network(ip, portTcp)
{
    this->initSystems();
    this->initComponents();
    this->initEntities();
    this->_network.run();
}

void eng::Client::initSystems()
{
    eng::SystemManager &systemManager = this->_engine.getECS().getSystemManager();
    eng::EntityManager &entityManager = this->_engine.getECS().getEntityManager();
    eng::Graphic &graphic = this->_engine.getGraphic();
    std::shared_ptr<std::vector<sf::Sprite>> sprites = std::make_shared<std::vector<sf::Sprite>>(this->_engine.getLoader().getSprites());
    std::shared_ptr<std::vector<sf::SoundBuffer>> sounds = std::make_shared<std::vector<sf::SoundBuffer>>(this->_engine.getLoader().getSounds());

    systemManager.addSystem(std::make_shared<eng::InputSystem>(graphic));
    systemManager.addSystem(std::make_shared<eng::PhysicSystem>(graphic));
    systemManager.addSystem(std::make_shared<eng::AnimationSystem>(graphic, sprites));
    systemManager.addSystem(std::make_shared<eng::RenderSystem>(graphic, sprites));
#ifndef NDEBUG
    systemManager.addSystem(std::make_shared<eng::GUISystem>(graphic));
#endif
    systemManager.addSystem(std::make_shared<eng::EnemySystem>(graphic));
    systemManager.addSystem(std::make_shared<eng::ScoreSystem>());
    systemManager.addSystem(std::make_shared<eng::SoundSystem>(graphic, sounds));

    entityManager.addMaskCategory(InfoComp::TEXT);
    entityManager.addMaskCategory(InfoComp::POS | InfoComp::SPRITEID);
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
    componentManager.bindComponent<Pattern>();
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

    parallaxPreload.preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    backgroundMusicPreload.preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    scoreTextPreload.preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
    vesselPreload.preload(this->_engine.getGraphic(), this->_engine.getECS().getEntityManager(), this->_engine.getECS().getComponentManager());
}

void eng::Client::mainLoop()
{
    _QUEUE_TYPE &dataIn = this->_network.getQueueIn();
    std::size_t refreshTick = 5;

    eng::Graphic &graphic = this->_engine.getGraphic();
    eng::ECS &ecs = this->_engine.getECS();
    eng::VesselPreload vesselPreload;

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
        for (size_t count = 0; count < refreshTick; count++) {
            if (!dataIn.empty()) {
                std::cout << "Message: " << dataIn.pop_front().data() << std::endl;
            } else {
                break;
            }
        }
        if (!this->_network.isConnected())
            graphic.getWindow()->close();
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

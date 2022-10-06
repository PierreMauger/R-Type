#include "Engine/Engine.hpp"
#include "Includes.hpp"

float createRandom(std::size_t min, std::size_t max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void createEnemy(eng::ECS &ecs)
{
    float posY = createRandom(0, 480);
    int type = createRandom(0, 2);
    std::size_t id = ecs.getEntityManager().getMasks().size();

    ecs.getEntityManager().addMask(id, (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID | eng::InfoEntity::ENEMY));
    ecs.getComponentManager().initEmptyComponent();
    ecs.getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{3});
    ecs.getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{800, posY, 0});
    ecs.getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, -2, 0});
    ecs.getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(type), 0, posY});
    ecs.getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
}

void mainLoop(eng::ECS &ecs, eng::Graphic &graphic)
{
    sf::Time elapsed_time = sf::seconds(0);
    sf::Time delta_time = sf::seconds(2);

    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
        }
        if (graphic.getClock()->getElapsedTime() > elapsed_time) {
            createEnemy(ecs);
            elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        }
        graphic.getWindow()->clear(sf::Color::Black);
        ecs.update();
        graphic.getWindow()->display();
    }
}

int main(void)
{
    eng::Engine engine;

    // graphic.loadSprites({"R-Type/assets/Sprites"});
    // graphic.loadSounds({"R-Type/assets/Sprites"});

    // setup system & component
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::InputSystem>(engine.getGraphic().getEvent(), engine.getGraphic().getClock()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::PhysicSystem>(engine.getGraphic().getWindow()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::RenderSystem>(engine.getGraphic().getWindow(), engine.getGraphic().getClock(), engine.getLoader()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::GUISystem>(engine.getGraphic().getWindow()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::PaternSystem>(engine.getGraphic().getClock()));

    engine.getECS().getComponentManager().addComponent(typeid(SpriteID), {});
    engine.getECS().getComponentManager().addComponent(typeid(Position), {});
    engine.getECS().getComponentManager().addComponent(typeid(Velocity), {});
    engine.getECS().getComponentManager().addComponent(typeid(Speed), {});
    engine.getECS().getComponentManager().addComponent(typeid(Controllable), {});
    engine.getECS().getComponentManager().addComponent(typeid(CooldownShoot), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parallax), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parent), {});
    engine.getECS().getComponentManager().addComponent(typeid(Patern), {});
    engine.getECS().getComponentManager().addComponent(typeid(Projectile), {});
    engine.getECS().getComponentManager().addComponent(typeid(Enemy), {});

    // create background
    engine.getECS().getEntityManager().addMask(0, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(0, SpriteID{6});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(0, Parallax{true});
    engine.getECS().getEntityManager().addMask(1, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(1, SpriteID{5});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{-0.6, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(1, Parallax{true});
    engine.getECS().getEntityManager().addMask(2, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(2, SpriteID{8});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(2, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(2, Velocity{-1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(2, Parallax{true});
    engine.getECS().getEntityManager().addMask(3, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(3, SpriteID{9});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(3, Position{0, 250, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(3, Velocity{-1.5, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(3, Parallax{true});
    engine.getECS().getEntityManager().addMask(4, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(4, SpriteID{7});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(4, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(4, Velocity{-2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(4, Parallax{true});

    // create spaceship
    engine.getECS().getEntityManager().addMask(5, (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(5, SpriteID{0});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(5, Position{10, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(5, Velocity{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Speed)).emplaceData(5, Speed{5});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(5, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(5, CooldownShoot{0, 0.5});

    // create cooldownBar
    engine.getECS().getEntityManager().addMask(6, (eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(6, SpriteID{2});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(6, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(6, Parent{6});

    mainLoop(engine.getECS(), engine.getGraphic());
    return 0;
}

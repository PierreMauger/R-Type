#include "Engine/Engine.hpp"
#include "Includes.hpp"

float createRandom(std::size_t min, std::size_t max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void createBoss(eng::ECS &ecs)
{
    std::size_t id = ecs.getEntityManager().getMasks().size();
    float posY = createRandom(50, 300);

    ecs.getEntityManager().addMask(id, (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::APP | eng::InfoEntity::SPRITEID | eng::InfoEntity::ENEMY |
                                        eng::InfoEntity::LIFE | eng::InfoEntity::SIZE));
    ecs.getComponentManager().initEmptyComponent();
    ecs.getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5, Priority::MEDIUM});
    ecs.getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, posY});
    ecs.getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{480, -300, 0});
    ecs.getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.5, -2, 0});
    ecs.getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(1), 0, posY - 2});
    ecs.getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, 0.4});
    ecs.getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{300, 259});
    ecs.getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{5});

    ecs.getEntityManager().addMask(id + 1, (eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT | eng::InfoEntity::LIFEBAR));
    ecs.getComponentManager().initEmptyComponent();
    ecs.getComponentManager().getComponent(typeid(Position)).emplaceData(id + 1, Position{480, 10, 0});
    ecs.getComponentManager().getComponent(typeid(Parent)).emplaceData(id + 1, Parent{id});
    ecs.getComponentManager().getComponent(typeid(LifeBar)).emplaceData(id + 1, LifeBar{true, 5});
    ecs.getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id + 1, SpriteID{2, Priority::MEDIUM});
}

void createEnemy(eng::ECS &ecs)
{
    float posY = createRandom(0, 480);
    int type = createRandom(0, 2);
    std::size_t id = ecs.getEntityManager().getMasks().size();

    ecs.getEntityManager().addMask(
        id, (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID | eng::InfoEntity::ENEMY | eng::InfoEntity::LIFE | eng::InfoEntity::SIZE));
    ecs.getComponentManager().initEmptyComponent();
    ecs.getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{3, Priority::MEDIUM});
    ecs.getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{800, posY, 0});
    ecs.getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, -2, 0});
    ecs.getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(type), 0, posY});
    ecs.getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, (float)(type == 0 ? 1.0 : 0.0)});
    ecs.getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{128, 120});
    ecs.getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{1});
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
        if (graphic.getClock()->getElapsedTime() > elapsed_time && graphic.getClock()->getElapsedTime().asSeconds() < 10) {
            createEnemy(ecs);
            elapsed_time = graphic.getClock()->getElapsedTime() + delta_time;
        } else if (graphic.getClock()->getElapsedTime() > elapsed_time && elapsed_time.asSeconds() != 0) {
            createBoss(ecs);
            elapsed_time = sf::seconds(0);
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
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::EnemySystem>(engine.getGraphic().getClock()));

    engine.getECS().getComponentManager().addComponent(typeid(SpriteID), {});
    engine.getECS().getComponentManager().addComponent(typeid(Position), {});
    engine.getECS().getComponentManager().addComponent(typeid(Velocity), {});
    engine.getECS().getComponentManager().addComponent(typeid(SpriteID), {});
    engine.getECS().getComponentManager().addComponent(typeid(Controllable), {});
    engine.getECS().getComponentManager().addComponent(typeid(CooldownShoot), {});
    engine.getECS().getComponentManager().addComponent(typeid(CooldownBar), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parallax), {});
    engine.getECS().getComponentManager().addComponent(typeid(Speed), {});
    engine.getECS().getComponentManager().addComponent(typeid(CooldownShoot), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parent), {});
    engine.getECS().getComponentManager().addComponent(typeid(Patern), {});
    engine.getECS().getComponentManager().addComponent(typeid(Projectile), {});
    engine.getECS().getComponentManager().addComponent(typeid(Enemy), {});
    engine.getECS().getComponentManager().addComponent(typeid(Life), {});
    engine.getECS().getComponentManager().addComponent(typeid(Size), {});
    engine.getECS().getComponentManager().addComponent(typeid(Appearance), {});
    engine.getECS().getComponentManager().addComponent(typeid(LifeBar), {});

    // create background
    engine.getECS().getEntityManager().addMask(0, (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(0, SpriteID{7, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(0, Parallax{true});
    engine.getECS().getEntityManager().addMask(1, (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(1, SpriteID{6, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{-0.6, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(1, Parallax{true});
    engine.getECS().getEntityManager().addMask(2, (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(2, SpriteID{8, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(2, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(2, Velocity{-1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(2, Parallax{true});
    engine.getECS().getEntityManager().addMask(3, (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(3, SpriteID{10, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(3, Position{0, 250, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(3, Velocity{-1.5, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(3, Parallax{true});
    engine.getECS().getEntityManager().addMask(4, (eng::InfoEntity::SPRITEID | eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::PARALLAX));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(4, SpriteID{9, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(4, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(4, Velocity{-2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(4, Parallax{true});

    // create spaceship
    engine.getECS().getEntityManager().addMask(
        5, (eng::InfoEntity::POS | eng::InfoEntity::LIFE | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID | eng::InfoEntity::CONTROLLABLE | eng::InfoEntity::COOLDOWNSHOOT));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(5, SpriteID{0, Priority::MEDIUM});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(5, Position{10, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(5, Velocity{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Speed)).emplaceData(5, Speed{5});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(5, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(5, CooldownShoot{0, 0.5});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(5, Size{100, 118});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(5, Life{1});

    // create cooldownBar
    engine.getECS().getEntityManager().addMask(6, (eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT | eng::InfoEntity::COOLDOWNBAR));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(6, SpriteID{2, Priority::HIGH});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(6, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(6, Parent{5});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(6, CooldownBar{true});

    mainLoop(engine.getECS(), engine.getGraphic());
    return 0;
}

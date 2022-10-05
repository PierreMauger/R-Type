#include "Engine/Engine.hpp"
#include "Includes.hpp"

void mainLoop(eng::ECS &ecs, eng::Graphic &graphic)
{
    while (graphic.getWindow()->isOpen()) {
        while (graphic.getWindow()->pollEvent(*graphic.getEvent())) {
            ImGui::SFML::ProcessEvent(*graphic.getEvent());
            if (graphic.getEvent()->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.getWindow()->close();
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
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::RenderSystem>(engine.getGraphic().getWindow(), engine.getGraphic().getClock()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::GUISystem>(engine.getGraphic().getWindow()));
    engine.getECS().getComponentManager().addComponent(typeid(SpriteID), {});

    engine.getECS().getComponentManager().addComponent(typeid(Position), {});
    engine.getECS().getComponentManager().addComponent(typeid(Velocity), {});
    engine.getECS().getComponentManager().addComponent(typeid(Speed), {});
    engine.getECS().getComponentManager().addComponent(typeid(Controllable), {});
    engine.getECS().getComponentManager().addComponent(typeid(CooldownShoot), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parallax), {});
    engine.getECS().getComponentManager().addComponent(typeid(Parent), {});

    // create background
    engine.getECS().getEntityManager().addMask(0, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(0, SpriteID{3});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(0, Parallax{true});
    engine.getECS().getEntityManager().addMask(1, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(1, SpriteID{3});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{800, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{-0.2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(1, Parallax{true});
    engine.getECS().getEntityManager().addMask(2, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(2, SpriteID{4});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(2, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(2, Velocity{-0.6, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(2, Parallax{true});
    engine.getECS().getEntityManager().addMask(3, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(3, SpriteID{5});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(3, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(3, Velocity{-1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(3, Parallax{true});
    engine.getECS().getEntityManager().addMask(4, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(4, SpriteID{6});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(4, Position{400, 250, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(4, Velocity{-1.5, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(4, Parallax{true});
    engine.getECS().getEntityManager().addMask(5, (eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(5, SpriteID{7});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(5, Position{800, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(5, Velocity{-2, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parallax)).emplaceData(5, Parallax{true});

    // create spaceship
    engine.getECS().getEntityManager().addMask(6, (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::SPRITEID));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(6, SpriteID{1});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(6, Position{10, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(6, Velocity{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Speed)).emplaceData(6, Speed{2});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(6, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(6, CooldownShoot{0, 2});

    // create cooldownBar
    engine.getECS().getEntityManager().addMask(7, (eng::InfoEntity::POS | eng::InfoEntity::SPRITEID | eng::InfoEntity::PARENT));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(7, SpriteID{8});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(7, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - 20, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(7, Parent{6});

    mainLoop(engine.getECS(), engine.getGraphic());
    return 0;
}

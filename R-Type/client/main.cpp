#include "Engine/Engine.hpp"
#include "Includes.hpp"

void mainLoop(eng::ECS ecs, eng::Graphic &graphic)
{
    while (graphic.isOpen()) {
        while (graphic.pollEvent()) {
            ImGui::SFML::ProcessEvent(graphic.getEvent());
            if (graphic.getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.close();
        }
        graphic.clear(sf::Color::Black);
        ecs.update();
        graphic.display();
    }
}

int main(void)
{
    eng::Engine engine;

    // setup system & component
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::InputSystem>(engine.getGraphic().getEvent()));
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::PhysicSystem>());
    engine.getECS().getSystemManager().addSystem(std::make_shared<eng::RenderSystem>(engine.getGraphic().getWindow()));
    engine.getECS().getComponentManager().addComponent(typeid(ModelID), {});
    engine.getECS().getComponentManager().addComponent(typeid(Position), {});
    engine.getECS().getComponentManager().addComponent(typeid(Velocity), {});
    engine.getECS().getComponentManager().addComponent(typeid(Speed), {});
    engine.getECS().getComponentManager().addComponent(typeid(Controllable), {});
    engine.getECS().getComponentManager().addComponent(typeid(CouldownShoot), {});

    // create background
    engine.getECS().getEntityManager().addMask(0, (eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{3});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{-0.2, 0, 0});
    engine.getECS().getEntityManager().addMask(1, (eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(1, ModelID{3});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{800, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{-0.2, 0, 0});
    engine.getECS().getEntityManager().addMask(2, (eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(2, ModelID{4});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(2, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(2, Velocity{-0.6, 0, 0});
    engine.getECS().getEntityManager().addMask(3, (eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(3, ModelID{5});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(3, Position{0, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(3, Velocity{-1, 0, 0});
    engine.getECS().getEntityManager().addMask(4, (eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(4, ModelID{6});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(4, Position{400, 250, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(4, Velocity{-1.5, 0, 0});
    engine.getECS().getEntityManager().addMask(5, (eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(5, ModelID{7});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(5, Position{800, 100, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(5, Velocity{-2, 0, 0});

    // create spaceship
    engine.getECS().getEntityManager().addMask(6, (eng::InfoEntity::POS | eng::InfoEntity::VEL | eng::InfoEntity::IDMODEL));
    engine.getECS().getComponentManager().initEmptyComponent();
    engine.getECS().getComponentManager().getComponent(typeid(ModelID)).emplaceData(6, ModelID{1});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(6, Position{10, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(6, Velocity{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Speed)).emplaceData(6, Speed{2});
    engine.getECS().getComponentManager().getComponent(typeid(Controllable)).emplaceData(6, Controllable{true});
    engine.getECS().getComponentManager().getComponent(typeid(CouldownShoot)).emplaceData(6, CouldownShoot{{}, sf::seconds(1)});

    mainLoop(engine.getECS(), engine.getGraphic());
    return 0;
}

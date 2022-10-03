#include "ECS/Game.hpp"
#include "Graphic/Graphic.hpp"
#include "Includes.hpp"

void mainLoop(ECS::Game &game, rdr::Graphic &graphic)
{
    while (graphic.isOpen()) {
        while (graphic.pollEvent()) {
            ImGui::SFML::ProcessEvent(graphic.getEvent());
            if (graphic.getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                graphic.close();
        }
        graphic.clear(sf::Color::Black);
        game.update();
        graphic.display();
    }
}

int main(void)
{
    ECS::Game game;
    rdr::Graphic graphic;

    // setup system & component
    game.getSystemManager().addSystem(std::make_shared<ECS::InputSystem>(graphic.getEvent()));
    game.getSystemManager().addSystem(std::make_shared<ECS::PhysicSystem>());
    game.getSystemManager().addSystem(std::make_shared<ECS::RenderSystem>(graphic.getWindow()));
    game.getComponentManager().addComponent(typeid(ModelID), {});
    game.getComponentManager().addComponent(typeid(Position), {});
    game.getComponentManager().addComponent(typeid(Velocity), {});
    game.getComponentManager().addComponent(typeid(Speed), {});
    game.getComponentManager().addComponent(typeid(Controllable), {});
    game.getComponentManager().addComponent(typeid(CouldownShoot), {});

    // create background
    game.getEntityManager().addMask(0, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{3});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{0, 0, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{-0.2, 0, 0});
    game.getEntityManager().addMask(1, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(1, ModelID{3});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{800, 0, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{-0.2, 0, 0});
    game.getEntityManager().addMask(2, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(2, ModelID{4});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(2, Position{0, 0, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(2, Velocity{-0.6, 0, 0});
    game.getEntityManager().addMask(3, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(3, ModelID{5});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(3, Position{0, 100, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(3, Velocity{-1, 0, 0});
    game.getEntityManager().addMask(4, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(4, ModelID{6});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(4, Position{400, 250, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(4, Velocity{-1.5, 0, 0});
    game.getEntityManager().addMask(5, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(5, ModelID{7});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(5, Position{800, 100, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(5, Velocity{-2, 0, 0});

    // create spaceship
    game.getEntityManager().addMask(6, (ECS::InfoEntity::POS | ECS::InfoEntity::VEL | ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(6, ModelID{1});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(6, Position{10, 0, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(6, Velocity{0, 0, 0});
    game.getComponentManager().getComponent(typeid(Speed)).emplaceData(6, Speed{2});
    game.getComponentManager().getComponent(typeid(Controllable)).emplaceData(6, Controllable{true});
    game.getComponentManager().getComponent(typeid(CouldownShoot)).emplaceData(6, CouldownShoot{{}, sf::seconds(1)});

    mainLoop(game, graphic);
    return 0;
}

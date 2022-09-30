#include "ECS/Game.hpp"
#include "Graphic/Graphic.hpp"
#include "Includes.hpp"

void mainLoop(ECS::Game &game, rdr::Graphic &graphic)
{
    while (graphic.isOpen()) {
        while (graphic.pollEvent()) {
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
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{0});

    // create spaceship
    game.getEntityManager().addMask(1, (ECS::InfoEntity::POS | ECS::InfoEntity::VEL | ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(1, ModelID{1});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{10, 0, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{0, 0, 0});
    game.getComponentManager().getComponent(typeid(Speed)).emplaceData(1, Speed{2});
    game.getComponentManager().getComponent(typeid(Controllable)).emplaceData(1, Controllable{true});
    game.getComponentManager().getComponent(typeid(CouldownShoot)).emplaceData(1, CouldownShoot{{}, sf::seconds(1)});

    mainLoop(game, graphic);
    return 0;
}

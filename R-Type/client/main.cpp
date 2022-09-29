#include "ECS/Game.hpp"
#include "graphic/Graphic.hpp"

void createBackground(ECS::Game &game)
{
    game.getComponentManager().addComponent(typeid(ModelID), {});
    game.getEntityManager().addMask(0, (ECS::InfoEntity::POS | ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{0});
}

void mainLoop(ECS::Game &game, rdr::Graphic &graphic)
{
    while (graphic.isOpen()) {
        while (graphic.pollEvent(graphic.getEvent()))
            if (graphic.getEvent().type == sf::Event::Closed)
                graphic.close();
        graphic.clear(sf::Color::Green);
        game.update();
        graphic.display();
    }
}

int main(void)
{
    ECS::Game game;
    rdr::Graphic graphic;

    //setup system & component
    game.getSystemManager().addSystem(std::make_shared<ECS::RenderSystem>(graphic.getWindow()));
    game.getSystemManager().addSystem(std::make_shared<ECS::PhysicSystem>());
    game.getComponentManager().addComponent(typeid(ModelID), {});
    game.getComponentManager().addComponent(typeid(Position), {});
    game.getComponentManager().addComponent(typeid(Velocity), {});

    //create background
    game.getEntityManager().addMask(0, (ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{0});

    //create spaceship
    game.getEntityManager().addMask(1, (ECS::InfoEntity::POS | ECS::InfoEntity::VEL | ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(1, ModelID{1});
    game.getComponentManager().getComponent(typeid(Position)).emplaceData(1, Position{10, 0, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(1, Velocity{2, 0, 0});

    mainLoop(game, graphic);
    return 0;
}

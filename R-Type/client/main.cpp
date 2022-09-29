#include "ECS/Game.hpp"
#include "Includes.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    ECS::Game game;

    game.getComponentManager().addComponent(typeid(Position), {});
    game.getComponentManager().addComponent(typeid(Velocity), {});
    game.getComponentManager().addComponent(typeid(ModelID), {});

    game.getEntityManager().addMask(0, (ECS::InfoEntity::POS | ECS::InfoEntity::IDMODEL));
    game.getComponentManager().initEmptyComponent();

    game.getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{10, 10, 0});
    game.getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{2, 2, 0});
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{1});

    game.getSystemManager().addSystem(std::make_shared<ECS::PhysicSystem>());
    game.getSystemManager().addSystem(std::make_shared<ECS::RenderSystem>());

    std::cout << std::any_cast<Position>(game.getComponentManager().getComponent(typeid(Position)).getField(0).value()).x << std::endl;
    game.update();
    std::cout << std::any_cast<Position>(game.getComponentManager().getComponent(typeid(Position)).getField(0).value()).x << std::endl;
    return 0;
}

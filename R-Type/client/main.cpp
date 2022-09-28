#include <any>

#include "Engine.hpp"
#include "Includes.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    ECS::Engine engine;

    engine.getComponentManager().addComponent(typeid(Position), {});
    engine.getComponentManager().addComponent(typeid(Velocity), {});
    engine.getComponentManager().addComponent(typeid(ModelID), {});

    engine.getEntityManager().addMask(0, (ECS::InfoEntity::POS | ECS::InfoEntity::IDMODEL));
    engine.getComponentManager().initEmptyComponent();

    engine.getComponentManager().getComponent(typeid(Position)).emplaceData(0, Position{10, 10, 0});
    engine.getComponentManager().getComponent(typeid(Velocity)).emplaceData(0, Velocity{2, 2, 0});
    engine.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{1});

    engine.getSystemManager().addSystem(std::make_shared<ECS::PhysicSystem>());
    engine.getSystemManager().addSystem(std::make_shared<ECS::RenderSystem>());

    std::cout << std::any_cast<Position>(engine.getComponentManager().getComponent(typeid(Position)).getField(0).value()).x << std::endl;
    engine.run();
    std::cout << std::any_cast<Position>(engine.getComponentManager().getComponent(typeid(Position)).getField(0).value()).x << std::endl;
    return 0;
}

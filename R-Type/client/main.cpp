#include "ECS/Game.hpp"
#include "Includes.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    ECS::Game game;
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "R-Type");

    game.getEntityManager().addMask(0, (ECS::InfoEntity::POS | ECS::InfoEntity::IDMODEL));
    game.getComponentManager().addComponent(typeid(ModelID), {});
    game.getComponentManager().initEmptyComponent();
    game.getComponentManager().getComponent(typeid(ModelID)).emplaceData(0, ModelID{1});
    game.getSystemManager().addSystem(std::make_shared<ECS::RenderSystem>(window));

    while (window->isOpen()) {
        game.update();
    }
    window.reset();
    return 0;
}

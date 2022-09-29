#include "Engine.hpp"
#include "Includes.hpp"

void mainLoop(ECS::Game &game, rdr::Graphic &graphic)
{
    while (graphic.isOpen()) {
        graphic.clear();
        game.update();
        graphic.display();
    }
}

int main(void)
{
    ECS::Game game;

    return 0;
}

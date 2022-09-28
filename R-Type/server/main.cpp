#include "Game.hpp"
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
    rdr::Graphic graphic;

    mainLoop(game, graphic);
    return 0;
}

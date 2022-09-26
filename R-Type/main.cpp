#include "Includes.hpp"
#include "Engine.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    ECS::Engine engine;

    engine.run();
    return 0;
}

#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./R-Type [portTcp]" << std::endl;
        return 84;
    }

    eng::Server server(std::stoi(av[1]));

    server.mainLoop();
    return 0;
}

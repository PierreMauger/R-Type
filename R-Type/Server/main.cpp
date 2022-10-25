#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./R-Type [ip] [portUdp] [portTcp]" << std::endl;
        return 84;
    }

    eng::Server server(std::stoi(av[1]), std::stoi(av[2]));

    server.mainLoop();

    return 0;
}

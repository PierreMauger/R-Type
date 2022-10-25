#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./R-Type [ip] [portUdp] [portTcp]" << std::endl;
        return 84;
    }

    eng::Client client(av[1], std::stoi(av[2]), std::stoi(av[3]));

    client.mainLoop();

    return 0;
}

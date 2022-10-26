#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./R-Type [ip] [portTcp]" << std::endl;
        return 1;
    }

    eng::Client client(av[1], std::stoi(av[2]));

    client.mainLoop();

    return 0;
}

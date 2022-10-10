#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./testCli <ip> <port>" << std::endl;
        return 84;
    }
    Client client(av[1], std::stoi(av[2]));
    client.run();
    client.open();
    client.close();
    return 0;
}
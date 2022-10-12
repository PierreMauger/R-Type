#include "Client.hpp"
#include <thread>

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./Client <ip> <portUdp> <portTcp>" << std::endl;
        return 84;
    }
    try {
        Client client(av[1], std::stoi(av[2]), std::stoi(av[3]));
        client.run();
        sleep(1);
        sleep(1);
        sleep(1);
        // client.udpMsg({'T'});
    } catch (std::exception &error) {
        std::cerr << "[CLIENT]: " << error.what() << std::endl;
    }
    return 0;
}
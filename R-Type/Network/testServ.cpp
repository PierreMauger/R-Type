#include "NetCommon.hpp"
#include "Server.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Usage: ./Server <portUdp> <portTcp>" << std::endl;
        return 84;
    }
    try {
        Server server(std::stoi(av[1]), std::stoi(av[2]));
        server.run();
        while (true) {
            sleep(1);
        }
    } catch (std::exception &error) {
        std::cerr << "[SERVER]: " << error.what() << std::endl;
    }
    return 0;
}
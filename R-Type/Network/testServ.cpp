#include "NetCommon.hpp"
#include "Server.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Usage: ./Server <portUdp> <portTcp>" << std::endl;
        return 84;
    }
    try {
        boost::asio::io_context io_context;
        Server server(io_context, std::stoi(av[1]), std::stoi(av[2]));
        io_context.run();
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}
#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./Client <ip> <portUdp> <portTcp>" << std::endl;
        return 84;
    }
    try {
        boost::asio::io_context io_context;
        Client client(io_context, av[1], std::stoi(av[2]), std::stoi(av[3]));
        client.tcpMsg({'H', 'E', 'L', 'L', 'O'});
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}
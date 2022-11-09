/**
 * @file main.cpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Main server file.
 * @copyright Epitech Rennes 2022
 */

/// @cond
#include "Server.hpp"

/// @endcond

/**
 * @brief Main function ran first when the r-type_server exectuable is launched.
 * @fn int main(int ac, char **av)
 */
int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./R-Type [portTcp]" << std::endl;
        return 84;
    }

    // init random
    time_t time = std::time(nullptr);
    std::srand(time);

    eng::Server server(std::stoi(av[1]), time);

    server.mainLoop();
    return 0;
}

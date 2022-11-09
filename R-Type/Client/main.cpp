/**
 * @file main.cpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Main client file that initializes the client then starts its main game loop.
 * @copyright Epitech Rennes 2022
 */

/// @cond
#include "Client.hpp"
/// @endcond

/**
 * @brief Main function ran first when the r-type_client exectuable is launched.
 * @details Initializes the engine and the client then start its main loop.
 * @fn int main(int ac, char **av)
 * @return The error code (1 if bad 0 if good)
 */
int main()
{
    eng::Client client;

    client.mainLoop();
    return 0;
}

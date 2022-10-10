#include "NetCommon.hpp"
#include "Server.hpp"

int main() {
    Server server(6000);
    server.run();
    return 0;
}
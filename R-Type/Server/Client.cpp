#include "Client.hpp"

eng::Client::Client(std::shared_ptr<Connection> connection)
    : _connection(connection)
{
}

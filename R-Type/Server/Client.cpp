#include "Client.hpp"

eng::Client::Client(std::shared_ptr<Connection> connection)
    : _connection(connection)
{
}

std::size_t eng::Client::getVesselId() const
{
    return _vesselId;
}

void eng::Client::setVesselId(std::size_t vesselId)
{
    _vesselId = vesselId;
}

bool eng::Client::isAlive() const
{
    return _isAlive;
}

void eng::Client::setAlive(bool isAlive)
{
    _isAlive = isAlive;
}

std::size_t eng::Client::getRoomId() const
{
    return _roomId;
}

void eng::Client::setRoomId(std::size_t roomId)
{
    _roomId = roomId;
}

bool eng::Client::isReady() const
{
    return _isReady;
}

void eng::Client::setReady(bool isReady)
{
    _isReady = isReady;
}

std::shared_ptr<eng::Connection> eng::Client::getConnection() const
{
    return _connection;
}

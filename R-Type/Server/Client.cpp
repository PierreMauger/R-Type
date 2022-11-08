#include "Client.hpp"

eng::Client::Client(std::shared_ptr<Connection> connection) : _connection(connection)
{
}

int eng::Client::getVesselId() const
{
    return _vesselId;
}

void eng::Client::setVesselId(int vesselId)
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

int eng::Client::getRoomId() const
{
    return _roomId;
}

void eng::Client::setRoomId(int roomId)
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

void eng::Client::destroyClient(std::vector<Room> &rooms, EntityManager &entityManager, ComponentManager &componentManager)
{
    if (this->_roomId != -1) {
        rooms[this->_roomId].removePlayer();
    }
    if (this->_vesselId != -1) {
        componentManager.removeAllComponents(this->_vesselId);
        entityManager.removeMask(this->_vesselId);
    }
}

bool eng::Client::operator==(const Client &client) const
{
    return (this->_vesselId == client._vesselId && this->_isAlive == client._isAlive && this->_roomId == client._roomId && this->_isReady == client._isReady && this->_connection == client._connection);
}

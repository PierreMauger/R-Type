#include "Client.hpp"

using namespace eng;

Client::Client(std::shared_ptr<Connection> connection, std::size_t id)
{
    this->_connection = connection;
    this->_id = id;

    connection->getTcpSocket().write_some(boost::asio::buffer(&this->_id, sizeof(this->_id)));
}

int Client::getVesselId() const
{
    return _vesselId;
}

void Client::setVesselId(int vesselId)
{
    _vesselId = vesselId;
}

bool Client::isAlive() const
{
    return _isAlive;
}

void Client::setAlive(bool isAlive)
{
    _isAlive = isAlive;
}

int Client::getRoomId() const
{
    return _roomId;
}

void Client::setRoomId(int roomId)
{
    _roomId = roomId;
}

bool Client::isReady() const
{
    return _isReady;
}

void Client::setReady(bool isReady)
{
    _isReady = isReady;
}

std::shared_ptr<Connection> Client::getConnection() const
{
    return _connection;
}

void Client::destroyClient(std::vector<Room> &rooms, EntityManager &entityManager, ComponentManager &componentManager)
{
    if (this->_roomId != -1) {
        rooms[this->_roomId].removePlayer();
    }
    if (this->_vesselId != -1) {
        componentManager.removeAllComponents(this->_vesselId);
        entityManager.removeMask(this->_vesselId);
    }
}

std::size_t Client::getId() const
{
    return _id;
}

bool Client::operator==(const Client &client) const
{
    return (this->_vesselId == client._vesselId && this->_isAlive == client._isAlive && this->_roomId == client._roomId && this->_isReady == client._isReady && this->_connection == client._connection);
}

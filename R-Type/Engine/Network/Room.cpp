#include "Room.hpp"

eng::Room::Room(std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers) : _id(id), _maxPlayers(maxPlayers), _nbPlayers(nbPlayers)
{
}

std::size_t eng::Room::getId() const
{
    return _id;
}

std::size_t eng::Room::getMaxPlayers() const
{
    return _maxPlayers;
}

std::size_t eng::Room::getNbPlayers() const
{
    return _nbPlayers;
}

void eng::Room::setId(std::size_t id)
{
    _id = id;
}

void eng::Room::setMaxPlayers(std::size_t maxPlayers)
{
    _maxPlayers = maxPlayers;
}

void eng::Room::setNbPlayers(std::size_t nbPlayers)
{
    _nbPlayers = nbPlayers;
}

void eng::Room::addPlayer()
{
    _nbPlayers++;
}

void eng::Room::removePlayer()
{
    _nbPlayers--;
}

bool eng::Room::isFull() const
{
    return _nbPlayers == _maxPlayers;
}

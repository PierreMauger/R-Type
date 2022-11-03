#include "Room.hpp"

using namespace eng;

Room::Room(std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers) : _id(id), _maxPlayers(maxPlayers), _nbPlayers(nbPlayers)
{
}

std::size_t Room::getId() const
{
    return _id;
}

std::size_t Room::getMaxPlayers() const
{
    return _maxPlayers;
}

std::size_t Room::getNbPlayers() const
{
    return _nbPlayers;
}

void Room::setId(std::size_t id)
{
    _id = id;
}

void Room::setMaxPlayers(std::size_t maxPlayers)
{
    _maxPlayers = maxPlayers;
}

void Room::setNbPlayers(std::size_t nbPlayers)
{
    _nbPlayers = nbPlayers;
}

void Room::addPlayer()
{
    _nbPlayers++;
}

void Room::removePlayer()
{
    _nbPlayers--;
}

bool Room::isFull() const
{
    return _nbPlayers == _maxPlayers;
}

bool Room::isStarted() const
{
    return _started;
}

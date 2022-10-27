#include "Room.hpp"

eng::Room::Room(std::size_t id, std::string name, std::size_t maxPlayers) : _id(id), _name(name), _maxPlayers(maxPlayers), _nbPlayers(0)
{
}

std::size_t eng::Room::getId() const
{
    return _id;
}

std::string eng::Room::getName() const
{
    return _name;
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

void eng::Room::setName(std::string name)
{
    _name = name;
}

void eng::Room::setMaxPlayers(std::size_t maxPlayers)
{
    _maxPlayers = maxPlayers;
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

#ifndef ROOM_HPP
#define ROOM_HPP

#include "Includes.hpp"

namespace eng
{
    class Room
    {
        private:
            std::size_t _id;
            std::size_t _maxPlayers;
            std::size_t _nbPlayers;

        public:
            Room(std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers = 0);
            ~Room() = default;

            std::size_t getId() const;
            std::size_t getMaxPlayers() const;
            std::size_t getNbPlayers() const;

            void setId(std::size_t id);
            void setMaxPlayers(std::size_t maxPlayers);
            void setNbPlayers(std::size_t nbPlayers);

            void addPlayer();
            void removePlayer();

            bool isFull() const;
    };
}

#endif // ROOM_HPP

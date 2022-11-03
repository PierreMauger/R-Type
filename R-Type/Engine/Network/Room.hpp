/**
 * @file Room.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The menu serializer
 * @copyright Epitech Rennes 2022
 */

#ifndef ROOM_HPP
#define ROOM_HPP

/// @cond
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief A room
     * @class Room
     */
    class Room
    {
        private:
            std::size_t _id;
            std::size_t _maxPlayers;
            std::size_t _nbPlayers;

        public:
            /**
             * @brief Room constructor.
             * @fn RoomSerializer()
             */
            Room(std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers = 0);
            /**
             * @brief Room destructor.
             * @fn ~RoomSerializer()
             */
            ~Room() = default;

            /**
             * @brief Get the id of the room
             * @fn std::size_t getId()
             * @return The room id
             */
            std::size_t getId() const;
            /**
             * @brief Get the max number of players of the room
             * @fn std::size_t getMaxPlayers()
             * @return The max number of players of the room
             */
            std::size_t getMaxPlayers() const;
            /**
             * @brief Get the number of players in the room
             * @fn std::size_t getNbPlayers()
             * @return The number of players in the room
             */
            std::size_t getNbPlayers() const;

            /**
             * @brief Set the id of the room
             * @fn void setId(std::size_t id)
             * @param id The id of the room
             */
            void setId(std::size_t id);
            /**
             * @brief Set the max number of players of the room
             * @fn void setMaxPlayers(std::size_t maxPlayers)
             * @param maxPlayers The max number of players of the room
             */
            void setMaxPlayers(std::size_t maxPlayers);
            /**
             * @brief Set the number of players in the room
             * @fn void setNbPlayers(std::size_t nbPlayers)
             * @param nbPlayers The number of players in the room
             */
            void setNbPlayers(std::size_t nbPlayers);

            /**
             * @brief Add a player in the room
             * @fn void addPlayer()
             */
            void addPlayer();
            /**
             * @brief Remove a player of the room
             * @fn void removePlayer()
             */
            void removePlayer();

            /**
             * @brief Check if the room is full
             * @fn bool isFull()
             * @return A boolean indicating if the room is full
             */
            bool isFull() const;
    };
}

#endif // ROOM_HPP

/**
 * @file Serializer.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The network serializer (formats packets to be sent through network).
 * @copyright Epitech Rennes 2022
*/

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

/// @cond
#include "Engine/Network/NetCommon.hpp"
#include "Includes.hpp"
/// @endcond

#define MAGIC "R-TYPE/AMOGUS"
#define MAGIC_SIZE sizeof(MAGIC)

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The type of operation to perform
     * @enum CrudType
    */
    enum CrudType {
        CREATE,
        DESTROY,
        UPDATE,

        UNKNOWN
    };
    /**
     * @brief The network serializer (formats packets to be sent through network).
     * @class Serializer
    */
    class Serializer
    {
        protected:
            template <typename T> void serializeData(std::vector<uint8_t> &packet, T *component)
            {
                for (uint8_t i = 0; i < sizeof(T); i++) {
                    packet.push_back(((uint8_t *)component)[i]);
                }
            };

            template <typename T> void deserializeData(std::vector<uint8_t> &packet, std::size_t &adv, T *component)
            {
                std::size_t i = 0;

                for (; i < sizeof(T); i++) {
                    ((uint8_t *)component)[i] = packet.at(adv + i);
                }
                adv += i;
            };

            void insertMagic(std::vector<uint8_t> &packet);
            bool checkMagic(std::vector<uint8_t> &packet, std::size_t adv);

            _STORAGE_DATA convertToData(std::vector<uint8_t> &packet);
            std::vector<uint8_t> convertToVector(_STORAGE_DATA &packet);

        public:
            /**
             * @brief Serializer constructor.
             * @fn Serializer()
            */
            Serializer();
            /**
             * @brief Serializer destructor.
             * @fn ~Serializer()
            */
            ~Serializer() = default;
    };
}

#endif // SERIALIZER_HPP

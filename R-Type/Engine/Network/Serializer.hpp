#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Engine/Network/NetCommon.hpp"
#include "Includes.hpp"

#define MAGIC "R-TYPE/AMOGUS"
#define MAGIC_SIZE sizeof(MAGIC)

namespace eng
{
    enum CrudType {
        CREATE,
        DESTROY,
        UPDATE,

        UNKNOWN
    };

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
            Serializer();
            ~Serializer() = default;
    };
}

#endif // SERIALIZER_HPP

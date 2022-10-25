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

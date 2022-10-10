#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Includes.hpp"

namespace eng
{
    enum PacketType {
        ENTITY,
        EVENT
    }

    class Serializer

    {
        private:
        public:
            Serializer();
            ~Serializer() = default;
    };
}

#endif // SERIALIZER_HPP

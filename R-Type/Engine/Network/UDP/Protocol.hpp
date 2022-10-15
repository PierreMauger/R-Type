#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#define MAGIC_NUMBER "R-TYPE/AMOGUS"

namespace eng
{
    enum PacketType {
        ENTITY,
        INPUT
    };

    enum EntityType {
        CREATE,
        DESTROY,
        UPDATE
    };
}

#endif // PROTOCOL_HPP

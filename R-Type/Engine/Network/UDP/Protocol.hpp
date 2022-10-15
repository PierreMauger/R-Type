#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#define MAGIC "R-TYPE/AMOGUS"
#define MAGIC_SIZE sizeof(MAGIC)

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

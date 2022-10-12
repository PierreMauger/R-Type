#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#define FOOTER "\n"

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

#include "Engine/Network/Serializer.hpp"

using namespace eng;

Serializer::Serializer()
{
}

_STORAGE_DATA eng::Serializer::convertToData(std::vector<uint8_t> &packet)
{
    _STORAGE_DATA convert = {0};

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert[i] = packet[i];
    }
    return convert;
}

std::vector<uint8_t> eng::Serializer::convertToVector(_STORAGE_DATA &packet)
{
    std::vector<uint8_t> convert;

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert.push_back(packet[i]);
    }
    return convert;
}

void eng::Serializer::insertMagic(std::vector<uint8_t> &packet)
{
    for (auto elem : MAGIC) {
        packet.push_back(elem);
    }
}

bool Serializer::checkMagic(std::vector<uint8_t> &packet, std::size_t adv)
{
    for (std::size_t i = 0; i < MAGIC_SIZE; i++) {
        if (packet[adv + i] != MAGIC[i]) {
            return false;
        }
    }
    return true;
}

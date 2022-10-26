#include "Engine/Network/MenuSerializer.hpp"

eng::MenuSerializer::MenuSerializer()
{
}

eng::Room eng::MenuSerializer::getRoom(std::vector<Room> rooms, std::size_t id)
{
    for (auto &room : rooms) {
        if (room.getId() == id) {
            return room;
        }
    }
    throw std::runtime_error("[ERROR] Room not found");
}

void eng::MenuSerializer::editRoom(CrudType crudType, std::vector<Room> &rooms, std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers)
{
    if (crudType == CrudType::CREATE) {
        rooms.push_back(Room(id, maxPlayers, nbPlayers));
        return;
    }

    Room room = getRoom(rooms, id);

    if (crudType == CrudType::DESTROY) {
        rooms.erase(std::remove(rooms.begin(), rooms.end(), room), rooms.end());
        return;
    }
    if (crudType == CrudType::UPDATE) {
        room.setNbPlayers(nbPlayers);
        room.setMaxPlayers(maxPlayers);
        return;
    }
    throw std::runtime_error("[ERROR] Invalid CRUD type");
}

_STORAGE_DATA eng::MenuSerializer::serializeRoomEdit(CrudType editType, Room &room)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    // header
    MenuPacketType menuPacketType = MenuPacketType::ROOM_EDIT;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &editType);

    // body
    std::size_t id = room.getId();
    std::size_t maxPlayers = room.getMaxPlayers();
    std::size_t nbPlayers = room.getNbPlayers();

    this->serializeData(packet, &id);
    this->serializeData(packet, &maxPlayers);
    this->serializeData(packet, &nbPlayers);

    insertMagic(packet);

    return this->convertToData(packet);
}

void eng::MenuSerializer::deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms)
{
    std::size_t adv = MAGIC_SIZE + sizeof(MenuPacketType);
    std::size_t id;
    std::size_t maxPlayers;
    std::size_t nbPlayers;
    CrudType crudType;

    this->deserializeData(packet, adv, &crudType);
    this->deserializeData(packet, adv, &id);
    this->deserializeData(packet, adv, &maxPlayers);
    this->deserializeData(packet, adv, &nbPlayers);

    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }

    this->editRoom(crudType, rooms, id, maxPlayers, nbPlayers);
}

_STORAGE_DATA eng::MenuSerializer::serializeRoomAction(std::size_t id, RoomAction action)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    // header
    MenuPacketType menuPacketType = MenuPacketType::ROOM_ACTION;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &action);

    // body
    this->serializeData(packet, &id);

    insertMagic(packet);

    return this->convertToData(packet);
}

void eng::MenuSerializer::deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms)
{
    std::size_t adv = MAGIC_SIZE + sizeof(MenuPacketType);
    std::size_t id;
    RoomAction action;

    this->deserializeData(packet, adv, &action);
    this->deserializeData(packet, adv, &id);

    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }

    // TODO: handle action
}

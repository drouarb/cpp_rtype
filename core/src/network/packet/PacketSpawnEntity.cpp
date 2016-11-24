//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketSpawnEntity.hh"

network::packet::PacketSpawnEntity::PacketSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName,
                                                      uint16_t entityId, uint16_t pos_x, uint16_t pos_y) :
        APacket
                (
                        SPAWN_ENTITY,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkString(spriteName.c_str()),
                                new utils::NetworkInteger(2, entityId),
                                new utils::NetworkInteger(2, pos_x),
                                new utils::NetworkInteger(2, pos_y)
                        }
                )
{

}

network::packet::PacketSpawnEntity::~PacketSpawnEntity()
{

}

void network::packet::PacketSpawnEntity::setTick(uint32_t tick)
{
SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketSpawnEntity::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketSpawnEntity::setEventId(uint16_t id)
{
SET_NETINT(schema, 1, id);
}

uint16_t network::packet::PacketSpawnEntity::getEventId() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketSpawnEntity::setSpriteName(const std::string &msg)
{
    SET_NETSTR(schema, 2, msg);
}

const network::utils::NetworkString &network::packet::PacketSpawnEntity::getSpriteName() const
{
    return GET_NETSTR(schema, 2);
}

void network::packet::PacketSpawnEntity::setEntityId(uint16_t entityId)
{
    SET_NETINT(schema, 3, entityId);
}

uint16_t network::packet::PacketSpawnEntity::getEntityId() const
{
    return GET_NETINT(schema, 3);
}

void network::packet::PacketSpawnEntity::setPosX(uint16_t pos_x)
{
    SET_NETINT(schema, 4, pos_x);
}

uint16_t network::packet::PacketSpawnEntity::getPosX() const
{
    return GET_NETINT(schema, 4);
}

void network::packet::PacketSpawnEntity::setPosY(uint16_t pos_y)
{
    SET_NETINT(schema, 5 , pos_y);
}

uint16_t network::packet::PacketSpawnEntity::getPosY() const
{
    return GET_NETINT(schema,5);
}

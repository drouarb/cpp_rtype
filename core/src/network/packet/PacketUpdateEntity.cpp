//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketUpdateEntity.hh"

network::packet::PacketUpdateEntity::PacketUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp) :
        APacket
                (
                        UPDATE_ENTITY,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkInteger(2, entityId),
                                new utils::NetworkInteger(2, hp)
                        }
                )
{

}
network::packet::PacketUpdateEntity::~PacketUpdateEntity()
{

}

void network::packet::PacketUpdateEntity::setTick(uint32_t tick)
{
    SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketUpdateEntity::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketUpdateEntity::setEventId(uint32_t id)
{
    SET_NETINT(schema, 1, id);
}

uint32_t network::packet::PacketUpdateEntity::getEventId() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketUpdateEntity::setEntityId(uint16_t entityId)
{
    SET_NETINT(schema, 2 , entityId);
}

uint16_t network::packet::PacketUpdateEntity::getEntityId() const
{
    return GET_NETINT(schema, 2);
}

void network::packet::PacketUpdateEntity::setHp(int16_t hp)
{
    SET_NETINT(schema, 3, hp);
}

int16_t network::packet::PacketUpdateEntity::getHp() const
{
    return GET_NETINT(schema, 3);
}

//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketDeleteEntity.hh"

network::packet::PacketDeleteEntity::PacketDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId) :
APacket
        (
                DELETE_ENTITY,
                {
                        new utils::NetworkInteger(4, tick),
                        new utils::NetworkInteger(4, eventId),
                        new utils::NetworkInteger(2, entityId)
                }
        )
{

}

network::packet::PacketDeleteEntity::~PacketDeleteEntity()
{

}

void network::packet::PacketDeleteEntity::setTick(uint32_t tick)
{
    SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketDeleteEntity::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketDeleteEntity::setEventId(uint32_t id)
{
    SET_NETINT(schema, 1, id);
}

uint16_t network::packet::PacketDeleteEntity::getEventId() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketDeleteEntity::setEntityId(uint16_t entityId)
{
    SET_NETINT(schema, 2 , entityId);
}

uint16_t network::packet::PacketDeleteEntity::getEntityId() const
{
    return GET_NETINT(schema, 2);
}

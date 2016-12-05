//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketMoveEntity.hh"
#include "network/packet/PacketMoveEntity.hh"

network::packet::PacketMoveEntity::PacketMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId , uint16_t vecX, uint16_t vecY) :
        APacket
                (
                        MOVE_ENTITY,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkInteger(2, entityId),
                                new utils::NetworkInteger(2, vecX),
                                new utils::NetworkInteger(2, vecY)
                        }
                )
{

}

network::packet::PacketMoveEntity::~PacketMoveEntity()
{

}

void network::packet::PacketMoveEntity::setTick(uint32_t tick)
{
    SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketMoveEntity::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketMoveEntity::setEventId(uint16_t id)
{
    SET_NETINT(schema, 1, id);
}

uint16_t network::packet::PacketMoveEntity::getEventId() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketMoveEntity::setEntityId(uint16_t entityId)
{
    SET_NETINT(schema, 2 , entityId);
}

uint16_t network::packet::PacketMoveEntity::getEntityId() const
{
    return GET_NETINT(schema, 2);
}

void network::packet::PacketMoveEntity::setVecX(uint16_t vecX)
{
    SET_NETINT(schema, 3, vecX);
}

uint16_t network::packet::PacketMoveEntity::getVecX() const
{
    return GET_NETINT(schema, 3);
}

void network::packet::PacketMoveEntity::setVecY(uint16_t vecY)
{
    SET_NETINT(schema, 4, vecY);
}

uint16_t network::packet::PacketMoveEntity::getVecY() const
{
    return GET_NETINT(schema, 4);
}

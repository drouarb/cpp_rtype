//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketMoveEntity.hh"


network::packet::PacketMoveEntity::PacketMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId , int16_t vecX, int16_t vecY, int16_t posx, int16_t posy ) :
        APacket
                (
                        MOVE_ENTITY,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkInteger(2, entityId),
                                new utils::NetworkInteger(2, vecX),
                                new utils::NetworkInteger(2, vecY),
                                new utils::NetworkInteger(2, posx),
                                new utils::NetworkInteger(2, posy)
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

void network::packet::PacketMoveEntity::setEventId(uint32_t id)
{
    SET_NETINT(schema, 1, id);
}

uint32_t network::packet::PacketMoveEntity::getEventId() const
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

void network::packet::PacketMoveEntity::setVecX(int16_t vecX)
{
    SET_NETINT(schema, 3, vecX);
}

int16_t network::packet::PacketMoveEntity::getVecX() const
{
    return GET_NETINT(schema, 3);
}

void network::packet::PacketMoveEntity::setVecY(int16_t vecY)
{
    SET_NETINT(schema, 4, vecY);
}

int16_t network::packet::PacketMoveEntity::getVecY() const
{
    return GET_NETINT(schema, 4);
}

void network::packet::PacketMoveEntity::setPosX(int16_t pos_x) {
    SET_NETINT(schema, 5, pos_x);
}

int16_t network::packet::PacketMoveEntity::getPosX() const {
    return  GET_NETINT(schema, 5);
}

void network::packet::PacketMoveEntity::setPosY(int16_t pos_y) {
    SET_NETINT(schema, 6, pos_y);
}

int16_t network::packet::PacketMoveEntity::getPosY() const {
    return GET_NETINT(schema, 6);
}

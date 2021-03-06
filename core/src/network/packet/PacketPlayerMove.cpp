//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketPlayerMove.hh"

network::packet::PacketPlayerMove::PacketPlayerMove(uint32_t tick, int32_t vect_x, int32_t vect_y,  int32_t pos_x, int32_t pos_y) :
        APacket
                (
                        PLAYER_MOVE,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, vect_x),
                                new utils::NetworkInteger(4, vect_y),
                                new utils::NetworkInteger(4, pos_x),
                                new utils::NetworkInteger(4, pos_y)

                        }
                )
{

}

network::packet::PacketPlayerMove::~PacketPlayerMove()
{

}

void network::packet::PacketPlayerMove::setTick(uint32_t tick)
{
    SET_NETINT(schema, 0, tick);
}

void network::packet::PacketPlayerMove::setVectX(int32_t vect_x)
{
    SET_NETINT(schema, 1, vect_x);
}

uint32_t network::packet::PacketPlayerMove::getTick() const
{
    return GET_NETINT(schema, 0);
}

int32_t network::packet::PacketPlayerMove::getVectX() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketPlayerMove::setVectY(int32_t vect_y)
{
    SET_NETINT(schema, 2, vect_y);
}

int32_t network::packet::PacketPlayerMove::getVectY() const
{
    return GET_NETINT(schema, 2);
}

void network::packet::PacketPlayerMove::setPosX(int32_t pos_x) {
    SET_NETINT(schema, 3, pos_x);
}

int32_t network::packet::PacketPlayerMove::getPosX() const {
    return GET_NETINT(schema, 3);
}

void network::packet::PacketPlayerMove::setPosY(int32_t pos_y) {
    SET_NETINT(schema, 4, pos_y);
}

int32_t network::packet::PacketPlayerMove::getPosY() const {
    return GET_NETINT(schema, 4);
}

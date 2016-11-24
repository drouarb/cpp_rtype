//
// Created by celeriy on 23/11/8.
//

#include "network/packet/PacketJoin.hh"


network::packet::PacketJoin::~PacketJoin()
{

}

void network::packet::PacketJoin::setJoin(uint8_t roomdId)
{
    SET_NETINT(schema, 0, roomdId);
}

uint8_t network::packet::PacketJoin::getJoin() const
{
    return GET_NETINT(schema, 0);
}

network::packet::PacketJoin::PacketJoin(uint8_t roomId) :
        APacket(
                JOIN,
                {
                        new utils::NetworkInteger(1, roomId)
                }

        )
{}

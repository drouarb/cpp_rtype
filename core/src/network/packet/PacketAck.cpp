//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketAck.hh"

network::packet::PacketAck::PacketAck(uint16_t ack) :
        APacket(
                ACK,
                {
                        new utils::NetworkInteger(2, ack)
                }
        )
{}

network::packet::PacketAck::~PacketAck()
{

}

void network::packet::PacketAck::setAck(uint16_t ack)
{
    SET_NETINT(schema, 0, ack);
}

uint16_t network::packet::PacketAck::getAck() const
{
    GET_NETINT(schema, 0);
    return 0;
}

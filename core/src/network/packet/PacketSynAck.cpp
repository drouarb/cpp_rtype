//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketSynAck.hh"

network::packet::PacketSynAck::PacketSynAck(uint16_t syn, uint16_t ack) :
        APacket
                (
                        SYN_ACK,
                        {
                                new utils::NetworkInteger(2, syn),
                                new utils::NetworkInteger(2, ack)
                        }
                )
{

}

network::packet::PacketSynAck::~PacketSynAck()
{

}

void network::packet::PacketSynAck::setAck(uint16_t ack)
{
    SET_NETINT(schema, 1, ack);
}

uint16_t network::packet::PacketSynAck::getAck() const
{
   return GET_NETINT(schema, 1);
}

uint16_t network::packet::PacketSynAck::getSyn() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketSynAck::setSyn(uint16_t syn)
{
    SET_NETINT(schema, 0, syn);
}

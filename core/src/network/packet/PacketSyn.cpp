//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketSyn.hh"

network::packet::PacketSyn::~PacketSyn()
{

}

void network::packet::PacketSyn::setSyn(uint16_t syn)
{
 SET_NETINT(schema, 0, syn);
}

uint16_t network::packet::PacketSyn::getSyn() const
{
    return GET_NETINT(schema, 0);
}

network::packet::PacketSyn::PacketSyn(uint16_t syn) :
        APacket(
                SYN,
                {
                        new utils::NetworkInteger(2, syn)
                }

        )
{}

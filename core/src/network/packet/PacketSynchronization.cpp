//
// Created by celeriy on 16/12/16.
//

#include "network/packet/PacketSynchronization.hh"

network::packet::PacketSynchronization::~PacketSynchronization()
{}

network::packet::PacketSynchronization::PacketSynchronization(uint32_t tick, int64_t time) :

        APacket
                (
                        SYNCHRONIZATION,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(8, time)
                        }
                )
{

}

void network::packet::PacketSynchronization::setTick(uint32_t tick) {
    SET_NETINT(schema, 0, tick);

}

uint32_t network::packet::PacketSynchronization::getTick() const {
    return GET_NETINT(schema, 0);
}

void network::packet::PacketSynchronization::setTime(int64_t time) {
    SET_NETINT(schema, 1 , time);
}

int64_t network::packet::PacketSynchronization::getTime() const {
    return GET_NETINT(schema, 1);
}

//
// Created by celeriy on 16/12/16.
//

#include "network/packet/PacketGameData.hh"

network::packet::PacketGameData::~PacketGameData()
{}

network::packet::PacketGameData::PacketGameData(uint32_t tick, int64_t time) :

        APacket
                (
                        GAME_DATA,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(8, time)
                        }
                )
{

}

void network::packet::PacketGameData::setTick(uint32_t tick) {
    SET_NETINT(schema, 0, tick);

}

uint32_t network::packet::PacketGameData::getTick() const {
    return GET_NETINT(schema, 0);
}

void network::packet::PacketGameData::setTime(int64_t time) {
    SET_NETINT(schema, 1 , time);
}

int64_t network::packet::PacketGameData::getTime() const {
    return GET_NETINT(schema, 1);
}

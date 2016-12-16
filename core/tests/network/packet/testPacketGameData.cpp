//
// Created by celeriy on 16/12/16.
//


#include <iostream>
#include <assert.h>
#include "network/packet/PacketGameData.cpp"
using namespace network;
using namespace packet;

void testPacketGameData()
{
    std::cout << "====Packet Player Attack Test====" << std::endl;
    t_rawdata data;
    PacketGameData *ack = new PacketGameData(UINT32_MAX, INT64_MAX);
    ack->serialize(&data);
    PacketGameData *ack2 = new PacketGameData;
    ack2->deserialize(&data);
    assert(ack->getTick() == UINT32_MAX);
    assert(ack->getTick() == ack2->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    assert(ack->getTime() == INT64_MAX);
    assert(ack->getTime() == ack2->getTime());
    std::cout << "SUCCESS getTime()" << std::endl;
    std::cout << "DONE" << std::endl;
}

int main()
{
    testPacketGameData();
    return (0);
}
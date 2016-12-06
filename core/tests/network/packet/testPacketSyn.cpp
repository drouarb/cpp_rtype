//
// Created by celeriy on 05/12/16.
//

#include "network/packet/PacketSyn.cpp"

#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketSyn()
{
    std::cout << "====Packet Syn Test====" << std::endl;
    t_rawdata data;
    PacketSyn *ack = new PacketSyn(UINT16_MAX);
    ack->serialize(&data);
    PacketSyn *ack2 = new PacketSyn();
    ack2->deserialize(&data);
    assert(ack2->getSyn() == UINT16_MAX);
    assert(ack->getSyn() == ack2->getSyn());
    std::cout << "SUCCESS getSyn()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testPacketSyn();
};
//
// Created by celeriy on 05/12/16.
//

#include "network/packet/PacketSynAck.cpp"

#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketSynAck()
{
    std::cout << "====Packet SynAck Test====" << std::endl;
    t_rawdata data;
    PacketSynAck *ack = new PacketSynAck(UINT16_MAX, 8989);
    ack->serialize(&data);
    PacketSynAck *ack2 = new PacketSynAck();
    ack2->deserialize(&data);
    assert(ack2->getAck() == 8989);
    assert(ack->getAck() == ack2->getAck());
    std::cout << "SUCCESS getAck()" << std::endl;
    assert(ack2->getSyn() ==  UINT16_MAX);
    assert(ack->getSyn() == ack2->getSyn());
    std::cout << "SUCCESS getSyn()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testPacketSynAck();
};
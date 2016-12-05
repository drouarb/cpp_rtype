
#include "network/packet/PacketJoin.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketJoin()
{
    std::cout << "====Packet Join Test====" << std::endl;
    t_rawdata data;
    PacketJoin *ack = new PacketJoin(UINT8_MAX);
    ack->serialize(&data);
    PacketJoin *ack2 = new PacketJoin();
    ack2->deserialize(&data);
    assert(ack->getJoin() == ack2->getJoin());
    std::cout << "SUCCESS getJoin()" << std::endl;
    std::cout << "DONE" << std::endl;
}


int main()
{
    testPacketJoin();
    return (0);
}
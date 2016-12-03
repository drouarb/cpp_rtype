
#include "network/packet/PacketAck.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketAck()
{
    std::cout << "====Packet Ack Test====" << std::endl;
    t_rawdata data;
    PacketAck *ack = new PacketAck(UINT16_MAX);
    ack->serialize(&data);
    PacketAck *ack2 = new PacketAck();
    ack2->deserialize(&data);
    assert(ack->getAck() == ack2->getAck());
    std::cout << "SUCCESS getAck()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testPacketAck();
};
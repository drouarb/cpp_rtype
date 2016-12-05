
#include "network/packet/PacketPong.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketPong()
{
    std::cout << "====Packet Pong Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketPong *pong = new network::packet::PacketPong("toto");
    pong->serialize(&data);
    network::packet::PacketPong *pong2 = new network::packet::PacketPong();
    pong2->deserialize(&data);
    assert(pong->getMessage().compare(pong2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testPacketPong();
};
#include "network/packet/PacketErrorScore.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketErrorScore()
{
    std::cout << "====Packet Error Score Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorScore *ping = new network::packet::PacketErrorScore("toto");
    ping->serialize(&data);
    network::packet::PacketErrorScore *ping2 = new network::packet::PacketErrorScore();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}

int main()
{
    testPacketErrorScore();
    return (0);
}
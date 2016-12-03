//
// Created by celeriy on 03/12/16.
//


#include "network/packet/PacketPing.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketPing()
{
    std::cout << "====Packet Ping Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketPing *ping = new network::packet::PacketPing("toto");
    ping->serialize(&data);
    network::packet::PacketPing *ping2 = new network::packet::PacketPing();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}

int main()
{
    testPacketPing();
    return (0);
}
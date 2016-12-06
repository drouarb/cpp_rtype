#include "network/packet/PacketErrorHandshake.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketErrorHandShake()
{
    std::cout << "====Packet test Error Handshake ====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorHandshake *pong = new network::packet::PacketErrorHandshake("toto");
    pong->serialize(&data);
    network::packet::PacketErrorHandshake *pong2 = new network::packet::PacketErrorHandshake();
    pong2->deserialize(&data);
    assert(pong->getMessage().compare("toto") == 0);
    assert(pong->getMessage().compare(pong2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testPacketErrorHandShake();
    return (0);
}
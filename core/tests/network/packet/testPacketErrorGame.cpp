#include "network/packet/PacketErrorGame.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;


void testPacketErrorGame()
{
    std::cout << "====Packet test Error Game ====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorGame *pong = new network::packet::PacketErrorGame("toto");
    pong->serialize(&data);
    network::packet::PacketErrorGame *pong2 = new network::packet::PacketErrorGame();
    pong2->deserialize(&data);
    assert(pong->getMessage().compare("toto") == 0);
    assert(pong->getMessage().compare(pong2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testPacketErrorGame();
    return (0);

}
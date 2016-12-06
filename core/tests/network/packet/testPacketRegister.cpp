//
// Created by celeriy on 05/12/16.
//

#include "network/packet/PacketRegister.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketRegister()
{
    std::cout << "====Packet Register Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketRegister *Register = new network::packet::PacketRegister("toto");
    Register->serialize(&data);
    network::packet::PacketRegister *Register2 = new network::packet::PacketRegister();
    Register2->deserialize(&data);
    assert(Register->getMessage().compare("toto") == 0);
    assert(Register->getMessage().compare(Register2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}

int main()
{
    testPacketRegister();
    return (0);
}

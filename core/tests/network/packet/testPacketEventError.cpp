
#include "network/packet/PacketEventError.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketEventError()
{
    std::cout << "====Packet Event Error Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketEventError *ping = new network::packet::PacketEventError("toto");
    ping->serialize(&data);
    network::packet::PacketEventError *ping2 = new network::packet::PacketEventError();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}
int main()
{
    testPacketEventError();
    return (0);
}
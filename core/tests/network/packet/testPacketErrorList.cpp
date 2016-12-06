#include "network/packet/PacketErrorList.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketErrorList()
{
    std::cout << "====Packet Error List Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorList *ping = new network::packet::PacketErrorList("toto");
    ping->serialize(&data);
    network::packet::PacketErrorList *ping2 = new network::packet::PacketErrorList();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare("toto") == 0);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}
int main()
{
    testPacketErrorList();
    return 0;
}
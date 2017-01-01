//
// Created by celeriy on 03/12/16.
//

#include "network/packet/PacketPlaySound.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketPlaySound()
{
    std::cout << "====Packet Player Move Test====" << std::endl;
    t_rawdata data;
    PacketPlaySound *ack = new PacketPlaySound(UINT32_MAX, UINT32_MAX, "");
    ack->serialize(&data);
    PacketPlaySound *ack2 = new PacketPlaySound();
    ack2->deserialize(&data);
    assert(ack->getTick() == UINT32_MAX);
    assert(ack->getTick() == ack2->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    assert(ack->getEventId() == UINT32_MAX);
    assert(ack->getEventId() == ack2->getEventId());
    std::cout << "SUCCESS getEventId" << std::endl;
    assert(std::string(ack->getSoundName().c_str()) == "");
    assert(std::string(ack->getSoundName().c_str()) == ack2->getSoundName());
    std::cout << "SUCCESS getSoundName()" << std::endl;
    std::cout << "DONE" << std::endl;
}
int main(){
    testPacketPlaySound();
    return (0);
}
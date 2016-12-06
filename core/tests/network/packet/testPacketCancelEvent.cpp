
#include "network/packet/PacketCancelEvent.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testCancelEvent()
{
    std::cout << "====Packet CancelEvent Test====" << std::endl;
    t_rawdata rawdata;
    PacketCancelEvent *event = new PacketCancelEvent(UINT32_MAX);
    event->serialize(&rawdata);
    PacketCancelEvent *event2 = new PacketCancelEvent();
    event2->deserialize(&rawdata);
    assert(event2->getCancelEvent() == UINT32_MAX);
    assert(event2->getCancelEvent() == event->getCancelEvent());
    std::cout << "SUCCESS getCancelEvent()" << std::endl;
    std::cout << "DONE" << std::endl;

}

int main()
{
    testCancelEvent();
    return (0);
}
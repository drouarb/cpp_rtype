//
// Created by celeriy on 05/12/16.
//

#include "network/packet/PacketUpdateEntity.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testUpdateEntity()
{    std::cout << "====Packet Move Entity Test====" << std::endl;
    t_rawdata data;
    PacketUpdateEntity *ack = new PacketUpdateEntity(UINT32_MAX, UINT32_MAX, UINT16_MAX , UINT16_MAX);
    ack->serialize(&data);
    PacketUpdateEntity *ack2 = new PacketUpdateEntity();
    ack2->deserialize(&data);
    assert(ack->getTick() == UINT32_MAX);
    assert(ack->getTick() == ack2->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    assert(ack->getEntityId() == UINT16_MAX);
    assert(ack->getEntityId() == ack2->getEntityId());
    std::cout << "SUCCESS getEntity()" << std::endl;
    assert(ack->getEventId() == UINT32_MAX);
    assert(ack->getEventId() == ack2->getEventId());
    std::cout << "SUCCESS getEventId()" << std::endl;
    assert(ack->getHp() == UINT16_MAX);
    assert(ack->getHp() == ack2->getHp());
    std::cout << "SUCCESS getHp()" << std::endl;
    std::cout << "DONE" << std::endl;
}

int main()
{
    testUpdateEntity();
    return (0);
}
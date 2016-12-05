//
// Created by celeriy on 03/12/16.
//

#include "network/packet/PacketMoveEntity.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketMoveEntity()
{
    std::cout << "====Packet Move Entity Test====" << std::endl;
    t_rawdata data;
    PacketMoveEntity *ack = new PacketMoveEntity(UINT32_MAX, 78787, UINT16_MAX, 1 , 989);
    ack->serialize(&data);
    PacketMoveEntity *ack2 = new PacketMoveEntity();
    ack2->deserialize(&data);
    assert(ack->getTick() == ack2->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    assert(ack->getEntityId() == ack2->getEntityId());
    std::cout << "SUCCESS getEntity()" << std::endl;
    assert(ack->getEventId() == ack2->getEventId());
    std::cout << "SUCCESS getEventId()" << std::endl;
    assert(ack->getVecX() == ack2->getVecX());
    std::cout << "SUCCESS getTVecX()" << std::endl;
    assert(ack->getVecY() == ack2->getVecY());
    std::cout << "SUCCESS getVeccY()" << std::endl;
    std::cout << "DONE" << std::endl;
}
int main()
{
    testPacketMoveEntity();
    return (0);
}
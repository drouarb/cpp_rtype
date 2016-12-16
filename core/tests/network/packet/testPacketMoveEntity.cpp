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
    PacketMoveEntity *ack = new PacketMoveEntity(UINT32_MAX, UINT32_MAX, UINT16_MAX, INT16_MAX , INT16_MAX, INT16_MAX, INT16_MAX);
    ack->serialize(&data);
    PacketMoveEntity *ack2 = new PacketMoveEntity();
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
    assert(ack->getVecX() == INT16_MAX);
    assert(ack->getVecX() == ack2->getVecX());
    std::cout << "SUCCESS getTVecX()" << std::endl;
    assert(ack->getVecY() == INT16_MAX);
    assert(ack->getVecY() == ack2->getVecY());
    std::cout << "SUCCESS getVeccY()" << std::endl;
    assert(ack->getPosX() == INT16_MAX);
    assert(ack->getPosX() == ack2->getPosX());
    std::cout << "SUCCESS getPosX" << std::endl;
    assert(ack->getPosY() == INT16_MAX);
    assert(ack->getPosY() == ack2->getPosY());
    std::cout << "SUCCESS getPosY" << std::endl;
    std::cout << "DONE" << std::endl;
}
int main()
{
    testPacketMoveEntity();
    return (0);
}
//
// Created by celeriy on 05/12/16.
//

#include "network/packet/PacketSpawnEntity.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testSpawnEntity()
{    std::cout << "====Packet Move Entity Test====" << std::endl;
    t_rawdata data;
    PacketSpawnEntity *ack = new PacketSpawnEntity(UINT32_MAX, UINT32_MAX, "toto", UINT16_MAX, INT16_MAX, INT16_MAX, INT16_MIN);
    ack->serialize(&data);
    PacketSpawnEntity *ack2 = new PacketSpawnEntity(0, 0,"kook", 0, 0, 0, 0);
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
    assert(ack->getPosX() == INT16_MAX);
    assert(ack->getPosX() == ack2->getPosX());
    std::cout << "SUCCESS getTPosX()" << std::endl;
    assert(ack->getPosY() == INT16_MAX);
    assert(ack->getPosY() == ack2->getPosY());
    std::cout << "SUCCESS getPoscY()" << std::endl;

    assert(ack->getHp() == INT16_MIN);
    assert(ack->getHp() == ack2->getHp());
    std::cout << "SUCCESS getHP()" << std::endl;
     std::cout << "DONE" << std::endl;
}

int main()
{
    testSpawnEntity();
    return (0);
}
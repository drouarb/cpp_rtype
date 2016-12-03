#include "network/packet/PacketDeleteEntity.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;
void testPacketDeleteEntity()
{
    std::cout << "=====Packet Delete Entity====" << std::endl;
    t_rawdata rawdata;
    PacketDeleteEntity *deleteEntity = new PacketDeleteEntity(UINT32_MAX, 89898, UINT16_MAX);
    deleteEntity->serialize(&rawdata);
    PacketDeleteEntity *deleteEntity2 = new PacketDeleteEntity;
    deleteEntity2->deserialize(&rawdata);
    assert(deleteEntity->getEntityId() == deleteEntity2->getEntityId());
    std::cout << "SUCCESS getEntityId()" << std::endl;
    assert(deleteEntity->getEventId() == deleteEntity2->getEventId());
    std::cout << "SUCCESS getEventId()" << std::endl;
    assert(deleteEntity2->getTick() == deleteEntity->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    std::cout << "DONE" << std::endl;
}


int main()
{
 testPacketDeleteEntity();
    return 0;
}
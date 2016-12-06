//
// Created by celeriy on 03/12/16.
//

#include "network/packet/PacketPlayerAttack.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketPlayerAttack()
{
    std::cout << "====Packet Player Attack Test====" << std::endl;
    t_rawdata data;
    PacketPlayerAttack *ack = new PacketPlayerAttack(UINT32_MAX, UINT8_MAX);
    ack->serialize(&data);
    PacketPlayerAttack *ack2 = new PacketPlayerAttack();
    ack2->deserialize(&data);
    assert(ack->getTick() == UINT32_MAX);
    assert(ack->getTick() == ack2->getTick());
    std::cout << "SUCCESS getTick()" << std::endl;
    assert(ack->getAttackId() == UINT8_MAX);
    assert(ack->getAttackId() == ack2->getAttackId());
    std::cout << "SUCCESS getAttackId()" << std::endl;
     std::cout << "DONE" << std::endl;
}

int main()
{
    testPacketPlayerAttack();
    return (0);
}
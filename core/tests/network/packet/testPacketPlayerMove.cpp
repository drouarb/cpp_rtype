//
// Created by celeriy on 03/12/16.
//

#include "network/packet/PacketPlayerMove.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketPlayerMove()
{
        std::cout << "====Packet Player Move Test====" << std::endl;
        t_rawdata data;
        PacketPlayerMove *ack = new PacketPlayerMove(UINT32_MAX, INT16_MAX, INT16_MAX, 10, 10);
        ack->serialize(&data);
        PacketPlayerMove *ack2 = new PacketPlayerMove();
        ack2->deserialize(&data);
        assert(ack->getTick() == UINT32_MAX);
        assert(ack->getTick() == ack2->getTick());
        std::cout << "SUCCESS getTick()" << std::endl;
        assert(ack->getVectX() == INT16_MAX);
        assert(ack->getVectX() == ack2->getVectX());
        std::cout << "SUCCESS getVectX()" << std::endl;
        assert(ack->getVectY() == INT16_MAX);
        assert(ack->getVectY() == ack2->getVectY());
        std::cout << "SUCCESS getVectY()" << std::endl;
        assert(ack->getPosX() == 10);
        std::cout << "SUCCESS getPosX()" << std::endl;
        assert(ack->getPosY() == 10);
        std::cout << "SUCCESS getPosY()" << std::endl;
        std::cout << "DONE" << std::endl;
}
int main()
{
    testPacketPlayerMove();
    return (0);
}
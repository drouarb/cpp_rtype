//
// Created by celeriy on 05/12/16.
//

#include "network/packet/PacketGameData.hh"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testUpdateEntity()
{    std::cout << "====Packet Game Data Test====" << std::endl;
    t_rawdata data;
    PacketGameData *gd = new PacketGameData("HELLO", "WORLD");
    gd->serialize(&data);
    PacketGameData *gd2 = new PacketGameData();
    gd2->deserialize(&data);
    assert(gd->getAudio() == "HELLO");
    assert(gd->getAudio() == gd2->getAudio());
    std::cout << "SUCCESS getAudio()" << std::endl;
    assert(gd->getBackground() == "WORLD");
    assert(gd->getBackground() == gd2->getBackground());
    std::cout << "SUCCESS getBackground()" << std::endl;
    std::cout << "DONE" << std::endl;
}

int main()
{
    testUpdateEntity();
    return (0);
}
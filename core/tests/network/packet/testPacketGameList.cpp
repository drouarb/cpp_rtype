
#include "network/packet/PacketGameList.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void testPacketgameList()
{
    std::cout << "====Packet GameList Test====" << std::endl;
    std::vector<std::pair<uint8_t , uint16_t>>toto;
    toto.push_back(std::pair<uint8_t , uint16_t >(UINT8_MAX, UINT16_MAX));
    toto.push_back(std::pair<uint8_t , uint16_t >(254, 9090));
    toto.push_back(std::pair<uint8_t , uint16_t >(2, 90));
    toto.push_back(std::pair<uint8_t , uint16_t >(125, 870));
    PacketGameList *list = new PacketGameList(toto);
    t_rawdata rawdata;
    list->serialize(&rawdata);
    PacketGameList *list2 = new PacketGameList;
    list2->deserialize(&rawdata);
    std::vector<std::pair<uint8_t , uint16_t>>it_list1 = list->getGameList();
    std::vector<std::pair<uint8_t , uint16_t>>it_list2 = list2->getGameList();
    std::cout << "getGameList() test" << std::endl;
    for (auto i = 0; i != it_list1.size(); i++)
    {
        assert(it_list1[i].first == it_list2[i].first);
        assert(it_list2[i].second == it_list1[i].second);
        std::cout << "SUCCESS  fist list1 =  " <<(int)it_list1[i].first << " list2 = "  << (int)it_list2[i].first << std::endl;
        std::cout << "SUCCESS second list2 = " <<(int)it_list1[i].second << " list2 = "  << it_list2[i].second << std::endl;
    }
    std::cout << "DONE" << std::endl;
}

int main()
{
    testPacketgameList();
    return (0);
}
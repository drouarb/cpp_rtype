//
// Created by celeriy on 03/12/16.
//

#include "network/packet/PacketLeaderBoard.cpp"
#include <iostream>
#include <assert.h>

using namespace network;
using namespace packet;

void test_LeaderBoard()
{
    std::cout << "====Packet LeaderBoard Test====" << std::endl;
    std::vector<std::pair<uint32_t , std::string>>toto;
    toto.push_back(std::pair<uint32_t , std::string >(UINT32_MAX, "kokokokok"));
    toto.push_back(std::pair<uint32_t , std::string >(254, "kokokoo"));
    toto.push_back(std::pair<uint32_t , std::string >(2, "kokoko"));
    toto.push_back(std::pair<uint32_t , std::string >(125, "ijiji"));
    PacketLeaderBoard *list = new PacketLeaderBoard(toto);
    t_rawdata rawdata;
    list->serialize(&rawdata);
    PacketLeaderBoard*list2 = new PacketLeaderBoard;
    list2->deserialize(&rawdata);
    std::vector<std::pair<uint32_t , std::string>>it_list1 = list->getLeaderBoard();
    std::vector<std::pair<uint32_t , std::string>>it_list2 = list2->getLeaderBoard();
    std::cout << "geLeaderBoard test" << std::endl;
    for (auto i = 0; i != it_list1.size(); i++)
    {
        assert(it_list1[i].first == it_list2[i].first);
        assert((it_list1[i].second.compare(it_list2[i].second)) == 0);
        std::cout << "SUCCESS  fist list1 =  " <<(int)it_list1[i].first << " list2 = "  << (int)it_list2[i].first << std::endl;
        std::cout << "SUCCESS second list2 = " <<(std::string)it_list1[i].second << " list2 = "  << (std::string)it_list2[i].second << std::endl;
    }
    std::cout << "DONE" << std::endl;
}
int main()
{
    test_LeaderBoard();
    return (0);
}
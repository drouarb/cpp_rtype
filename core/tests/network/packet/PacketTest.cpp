//
// Created by celeriy on 02/12/16.
//
#include "network/packet/PacketJoin.cpp"
#include "network/packet/PacketGameList.cpp"
#include "network/packet/PacketEventError.cpp"
#include "network/packet/PacketErrorList.cpp"
#include "network/packet/PacketErrorScore.cpp"
#include "network/packet/PacketErrorHandshake.cpp"
#include "network/packet/PacketErrorGame.cpp"
#include "network/packet/PacketDeleteEntity.cpp"
#include "network/packet/PacketPing.cpp"
#include "network/packet/PacketPong.cpp"
#include "network/packet/PacketAck.cpp"
#include "network/packet/PacketCancelEvent.cpp"
#include <assert.h>
#include <iostream>


using namespace network;
using namespace packet;

void testPacketPing()
{
    std::cout << "====Packet Ping Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketPing *ping = new network::packet::PacketPing("toto");
    ping->serialize(&data);
    network::packet::PacketPing *ping2 = new network::packet::PacketPing();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}

void testPacketErrorList()
{
    std::cout << "====Packet Error List Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorList *ping = new network::packet::PacketErrorList("toto");
    ping->serialize(&data);
    network::packet::PacketErrorList *ping2 = new network::packet::PacketErrorList();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}
void testPacketErrorScore()
{
    std::cout << "====Packet Error Score Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorScore *ping = new network::packet::PacketErrorScore("toto");
    ping->serialize(&data);
    network::packet::PacketErrorScore *ping2 = new network::packet::PacketErrorScore();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}

void testPacketEventError()
{
    std::cout << "====Packet Event Error Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketEventError *ping = new network::packet::PacketEventError("toto");
    ping->serialize(&data);
    network::packet::PacketEventError *ping2 = new network::packet::PacketEventError();
    ping2->deserialize(&data);
    assert(ping->getMessage().compare(ping2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;
}
void testPacketPong()
{
    std::cout << "====Packet Pong Test====" << std::endl;
    t_rawdata data;
    network::packet::PacketPong *pong = new network::packet::PacketPong("toto");
    pong->serialize(&data);
    network::packet::PacketPong *pong2 = new network::packet::PacketPong();
    pong2->deserialize(&data);
    assert(pong->getMessage().compare(pong2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;

}


void testPacketErrorGame()
{
    std::cout << "====Packet test Error Game ====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorGame *pong = new network::packet::PacketErrorGame("toto");
    pong->serialize(&data);
    network::packet::PacketErrorGame *pong2 = new network::packet::PacketErrorGame();
    pong2->deserialize(&data);
    assert(pong->getMessage().compare(pong2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;

}

void testPacketErrorHandShake()
{
    std::cout << "====Packet test Error Handshake ====" << std::endl;
    t_rawdata data;
    network::packet::PacketErrorHandshake *pong = new network::packet::PacketErrorHandshake("toto");
    pong->serialize(&data);
    network::packet::PacketErrorHandshake *pong2 = new network::packet::PacketErrorHandshake();
    pong2->deserialize(&data);
    assert(pong->getMessage().compare(pong2->getMessage()) == 0);
    std::cout << "SUCCESS getMessage()" << std::endl;
    std::cout << "DONE" << std::endl;

}

void testPacketAck()
{
    std::cout << "====Packet Ack Test====" << std::endl;
    t_rawdata data;
    PacketAck *ack = new PacketAck(UINT16_MAX);
    ack->serialize(&data);
    PacketAck *ack2 = new PacketAck();
    ack2->deserialize(&data);
    assert(ack->getAck() == ack2->getAck());
    std::cout << "SUCCESS getAck()" << std::endl;
    std::cout << "DONE" << std::endl;

}

void testPacketJoin()
{
std::cout << "====Packet Join Test====" << std::endl;
t_rawdata data;
PacketJoin *ack = new PacketJoin(UINT8_MAX);
ack->serialize(&data);
PacketJoin*ack2 = new PacketJoin();
ack2->deserialize(&data);
assert(ack->getJoin() == ack2->getJoin());
std::cout << "SUCCESS getJoin()" << std::endl;
std::cout << "DONE" << std::endl;

}

void testCancelEvent()
{
    std::cout << "====Packet CancelEvent Test====" << std::endl;
    t_rawdata rawdata;
    PacketCancelEvent *event = new PacketCancelEvent(UINT32_MAX);
    event->serialize(&rawdata);
    PacketCancelEvent *event2 = new PacketCancelEvent();
    event2->deserialize(&rawdata);
    assert(event2->getCancelEvent() == event->getCancelEvent());
    std::cout << "SUCCESS getCancelEvent()" << std::endl;
    std::cout << "DONE" << std::endl;

}

void testPacketDeleteEntity()
{
    std::cout << "=====Packet Delete Entity====" << std::endl;
    t_rawdata rawdata;
    PacketDeleteEntity *deleteEntity = new PacketDeleteEntity(UINT32_MAX, UINT32_MAX, UINT16_MAX);
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
        std::cout << "SUCCESS  fist list1 =  " <<(int)it_list1[i].first << " list2 = "  << (int)it_list2[i].first << std::endl;
        std::cout << "SUCCESS second list2 = " <<(int)it_list1[i].second << " list2 = "  << it_list2[i].second << std::endl;
    }
    std::cout << "DONE" << std::endl;
}
int main()
{
    testPacketPing();
    testPacketPong();
    testPacketAck();
    testCancelEvent();
    testPacketDeleteEntity();
    testPacketErrorGame();
    testPacketErrorHandShake();
    testPacketErrorList();
    testPacketErrorScore();
    testPacketEventError();
    testPacketgameList();
    testPacketJoin();
    return (0);
}
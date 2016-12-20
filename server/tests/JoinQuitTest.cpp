//
// Created by greg on 09/12/2016.
//

#include <network/packet/PacketJoin.hh>
#include <network/packet/PacketDisconnect.hh>
#include <cassert>
#include <listeners/ServerListenerJoin.hh>
#include "ProjTester.hpp"

void toTest(NetworkManagerTest &networkManagerTest, CoreTest &coreTest)
{
    network::packet::PacketJoin *packetJoin = new network::packet::PacketJoin();
    network::packet::PacketDisconnect *packetDisconnect = new network::packet::PacketDisconnect();

    server::ServerListenerJoin *join = new server::ServerListenerJoin(&networkManagerTest);


    networkManagerTest.clientConnect(42);
    packetDisconnect->setSource(42);
    packetJoin->setSource(42);
    packetJoin->setJoin(1);
    join->notify(packetJoin);
    assert(status[NETWORK_MANAGER_clientJoin]);
}
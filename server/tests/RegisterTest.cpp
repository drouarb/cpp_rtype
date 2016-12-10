//
// Created by greg on 09/12/2016.
//

#include <network/packet/PacketRegister.hh>
#include <listeners/ServerListenerRegister.hh>
#include <cassert>
#include "ProjTester.hpp"

void toTest(NetworkManagerTest &networkManagerTest, CoreTest &coreTest)
{
    network::packet::PacketRegister *aRegister = new network::packet::PacketRegister("");
    aRegister->setSource(42);
    aRegister->setMessage("greg");

    server::ServerListenerRegister *listenerRegister = new server::ServerListenerRegister(&networkManagerTest);
    listenerRegister->notify(aRegister);
    assert(status[NETWORK_MANAGER_clientRegister]);
}
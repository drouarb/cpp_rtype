//
// Created by greg on 09/12/2016.
//

#include <network/packet/PacketRegister.hh>
#include <listeners/ServerListenerRegister.hh>
#include <cassert>
#include <iostream>
#include "ProjTester.hpp"

void toTest(NetworkManagerTest &networkManagerTest, CoreTest &coreTest) {
    network::packet::PacketRegister *aRegister = new network::packet::PacketRegister("");
    aRegister->setSource(42);
    aRegister->setMessage("greg");

    server::ServerListenerRegister *listenerRegister = new server::ServerListenerRegister(&networkManagerTest);
    try {
        listenerRegister->notify(aRegister);
        assert(true);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
        assert(false); //Doit réussir, le paquet peut être envoyé avant un JOIN
    }
    assert(status[NETWORK_MANAGER_clientRegister]);
}
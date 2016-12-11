//
// Created by greg on 10/12/2016.
//

#include <cassert>
#include "ProjTester.hpp"
#include <network/packet/PacketPlayerAttack.hh>
#include <network/packet/PacketPlayerMove.hh>
#include <listeners/ServerListenerPlayerAttack.hh>
#include <listeners/ServerListenerPlayerMove.hh>
#include <iostream>
#include <network/packet/PacketJoin.hh>
#include <listeners/ServerListenerJoin.hh>

void toTest(NetworkManagerTest &networkManagerTest, CoreTest &coreTest)
{
    network::packet::PacketPlayerAttack *packetPlayerAttack = new network::packet::PacketPlayerAttack();
    network::packet::PacketPlayerMove *packetPlayerMove = new network::packet::PacketPlayerMove();

    server::ServerListenerPlayerAttack *playerAttack = new server::ServerListenerPlayerAttack(&networkManagerTest);
    server::ServerListenerPlayerMove *playerMove = new server::ServerListenerPlayerMove(&networkManagerTest);

    packetPlayerMove->setSource(42);
    packetPlayerAttack->setSource(42);

    packetPlayerMove->setTick(1);
    packetPlayerMove->setVectX(4);
    packetPlayerMove->setVectY(4);

    packetPlayerAttack->setTick(1);
    packetPlayerAttack->setAttackId(1);

    try {
        playerAttack->notify(packetPlayerAttack);
        playerMove->notify(packetPlayerMove);
        assert(false);
    }catch (std::logic_error) {
        std::cout << "END" << std::endl;
        assert(true); //Must throw cause client was not connected
    }
    assert(!status[NETWORK_MANAGER_clientPlayerAttack]);
    assert(!status[NETWORK_MANAGER_clientPlayerMove]);

    networkManagerTest.createClient(42);

    try {
        playerAttack->notify(packetPlayerAttack);
        playerMove->notify(packetPlayerMove);
        assert(false);
    }catch (std::logic_error) {
        std::cout << "END" << std::endl;
        assert(true); //Must throw cause no join was made
    }

    assert(!status[NETWORK_MANAGER_clientPlayerAttack]);
    assert(!status[NETWORK_MANAGER_clientPlayerMove]);

    network::packet::PacketJoin *packetJoin = new network::packet::PacketJoin();
    server::ServerListenerJoin *join = new server::ServerListenerJoin(&networkManagerTest);

    packetJoin->setSource(42);
    packetJoin->setJoin(1);



    try {
        join->notify(packetJoin);
        playerAttack->notify(packetPlayerAttack);
        return;
        playerMove->notify(packetPlayerMove);
        assert(true);
    }catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
        assert(false);
    }catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    assert(status[NETWORK_MANAGER_clientPlayerAttack]);
    assert(status[NETWORK_MANAGER_clientPlayerMove]);




}
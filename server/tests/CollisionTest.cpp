//
// Created by greg on 15/12/2016.
//

#include <listeners/ServerListenerDisconnect.hh>
#include <listeners/ServerListenerJoin.hh>
#include <cassert>
#include <network/packet/PacketPlayerAttack.hh>
#include <network/packet/PacketPlayerMove.hh>
#include <listeners/ServerListenerPlayerAttack.hh>
#include <listeners/ServerListenerPlayerMove.hh>
#include <iostream>
#include <thread/Thread.hpp>
#include "ProjTester.hpp"


void run(CoreTest *coreTest) {
    coreTest->run();
}

void toTest(NetworkManagerTest &networkManagerTest, CoreTest &coreTest)
{
    Thread<void (*)(CoreTest *), CoreTest *> *thread = new Thread<void (*)(CoreTest *), CoreTest *>(&run, &coreTest);

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

    assert(!status[NETWORK_MANAGER_clientPlayerAttack]);
    assert(!status[NETWORK_MANAGER_clientPlayerMove]);

    networkManagerTest.clientConnect(42);

    network::packet::PacketJoin *packetJoin = new network::packet::PacketJoin();
    server::ServerListenerJoin *join = new server::ServerListenerJoin(&networkManagerTest);

    packetJoin->setSource(42);
    packetJoin->setJoin(1);

    
    try {
        join->notify(packetJoin);
        playerAttack->notify(packetPlayerAttack);
        playerMove->notify(packetPlayerMove);
        assert(true);
    }catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
        assert(false);
    }catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        assert(false);
    }

    assert(status[NETWORK_MANAGER_clientPlayerAttack]);
    assert(status[NETWORK_MANAGER_clientPlayerMove]);

    INFO("END OF TEST")

    IStopwatch *pStopwatch = IStopwatch::getInstance();
    pStopwatch->set();
    while (pStopwatch->ellapsedMs() < 5000) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    thread->detach();

}
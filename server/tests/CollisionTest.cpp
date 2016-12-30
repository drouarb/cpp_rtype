//
// Created by greg on 15/12/2016.
//

#include <listeners/ServerListenerJoin.hh>
#include <cassert>
#include <network/packet/PacketPlayerAttack.hh>
#include <network/packet/PacketPlayerMove.hh>
#include <listeners/ServerListenerPlayerAttack.hh>
#include <listeners/ServerListenerPlayerMove.hh>
#include <iostream>
#include <thread/Thread.hpp>
#include "ProjTester.hpp"


static const int test_duration = 1000;

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
    packetPlayerMove->setVectX(0);
    packetPlayerMove->setVectY(0);

    packetPlayerAttack->setTick(32);
    packetPlayerAttack->setAttackId(1);


    networkManagerTest.clientConnect(42);

    network::packet::PacketJoin *packetJoin = new network::packet::PacketJoin();
    server::ServerListenerJoin *join = new server::ServerListenerJoin(&networkManagerTest);

    packetJoin->setSource(42);
    packetJoin->setJoin(1);

    
    try {
        join->notify(packetJoin);
        playerMove->notify(packetPlayerMove);
//        playerAttack->notify(packetPlayerAttack);
        assert(true);
    }catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
        assert(false);
    }catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        assert(false);
    }



    helpers::IStopwatch *pStopwatch = helpers::IStopwatch::getInstance();
    pStopwatch->set();
    uint32_t i = 0;
    while (pStopwatch->elapsedMs() < test_duration) {
        ++i;
        packetPlayerAttack->setTick(32 + i);
        if (i < 6)
            playerAttack->notify(packetPlayerAttack);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
   }
    thread->detach();

    INFO("END OF TEST")
}
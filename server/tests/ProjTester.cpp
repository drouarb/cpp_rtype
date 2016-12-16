//
// Created by greg on 09/12/2016.
//

#include <iostream>
#include "ProjTester.hpp"
#include "definitions.hh"


std::map<METHOD_CALLED, bool> status;


void CoreTest::run(server::round_t maxTick) {
    server::Core::run();
}

void CoreTest::setClient(server::Client &client, int id) {
    server::Core::setClient(client, id);
    status[CORE_SET_CLIENT] = true;
}

void CoreTest::removeClient(server::Client &client) {
    server::Core::removeClient(client);
    status[CORE_REMOVE_CLIENT] = true;
}

void CoreTest::run() {
    server::Core::run();
}

NetworkManagerTest::NetworkManagerTest(server::Core *core) : NetworkManager(core) {}

void NetworkManagerTest::setCore(server::Core *core) {
    this->core = core;
}

void NetworkManagerTest::clientRegister(int src, const std::string &name) {
    server::NetworkManager::clientRegister(src, name);
    status[NETWORK_MANAGER_clientRegister] = true;
}

void NetworkManagerTest::clientDisconnect(int src) {
    server::NetworkManager::clientDisconnect(src);
    status[NETWORK_MANAGER_clientDisconnect] = true;
}

void NetworkManagerTest::clientJoin(int src, server::gameId_t game) {
    server::NetworkManager::clientJoin(src, game);
    status[NETWORK_MANAGER_clientJoin] = true;
}

void NetworkManagerTest::clientPlayerAttack(int src, server::attackId_t attackId, server::round_t tick) {
    server::NetworkManager::clientPlayerAttack(src, attackId, tick);
    status[NETWORK_MANAGER_clientPlayerAttack] = true;
}

void NetworkManagerTest::clientPlayerMove(int src, server::speed_t vectX, server::speed_t vectY)
{
    server::NetworkManager::clientPlayerMove(src, vectX, vectY);
    status[NETWORK_MANAGER_clientPlayerMove] = true;
}

void NetworkManagerTest::clientPlayerQuit(int src) {
    server::NetworkManager::clientPlayerQuit(src);
    status[NETWORK_MANAGER_clientPlayerQuit] = true;
}

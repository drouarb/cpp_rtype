#include <NetworkManager.hh>
#include <iostream>
#include <thread/Mutexer.hh>
#include <thread/Mutex.hh>

server::NetworkManager::NetworkManager(server::Core *core) : core(core), mutex(new Mutex()) {}

const std::list<server::Client> &server::NetworkManager::getClientList() const {
    return this->clientContainer.toStdList();
}

void server::NetworkManager::sendGameState(int hp, server::clientId_t clientId) {
    Mutexer(this->mutex);
}

void server::NetworkManager::sendMessage(const std::string &msg, server::clientId_t clientId) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get(clientId);
}

void server::NetworkManager::clientRegister(int src, const std::string &name) {
    Mutexer(this->mutex);
    try {
        Client &client = this->clientContainer.get(src);
        client.setName(name);
    } catch (std::logic_error &e) {
        Client &client = this->clientContainer.create(src);
        client.setName(name);
    }
}

void server::NetworkManager::clientDisconnect(int src) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get(src);
    core->removeClient(client);
    this->clientContainer.remove(src);
}

void server::NetworkManager::clientConnect(int src) {
    Mutexer(this->mutex);
    clientContainer.create(src);
}

void server::NetworkManager::clientJoin(int src, gameId_t game) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get(src);
    core->setClient(client, game);
}

void server::NetworkManager::clientPlayerAttack(int src, attackId_t attackId, round_t tick) {
    //TODO Use tick
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get(src);
    if (client.getController())
        client.getController()->playShoot(attackId);
}

void server::NetworkManager::clientPlayerMove(int src, speed_t vectX, speed_t vectY) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get(src);
    if (client.getController())
        client.getController()->playMove(vectX, vectY);
}

void server::NetworkManager::clientPlayerQuit(int src) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get(src);
    core->removeClient(client);
}

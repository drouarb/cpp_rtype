#include <NetworkManager.hh>
#include <iostream>
#include <thread/Mutexer.hh>
#include <network/packet/PacketGameList.hh>
#include <network/packet/PacketLeaderBoard.hh>

server::NetworkManager::NetworkManager(server::Core *core) : core(core), mutex(new Mutex()), connectionListener(
        new ConnectionListener(this->clientContainer)), disconnectionListener(
        new DisconnectionListener(this->clientContainer, core)) {}

server::NetworkManager::~NetworkManager() {

}

const std::list<server::Client> &server::NetworkManager::getClientList() const {
    return this->clientContainer.toStdList();
}

void server::NetworkManager::sendGameState(int hp, server::clientId_t clientId) {
    Mutexer(this->mutex);
}

void server::NetworkManager::sendMessage(const std::string &msg, server::clientId_t clientId) {
    Mutexer(this->mutex);
//    Client &client = this->clientContainer.get(clientId);
}

void server::NetworkManager::clientRegister(clientId_t src, const std::string &name) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get((src));
    client.setName(name);
}

void server::NetworkManager::clientDisconnect(clientId_t src) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get((src));
    core->removeClient(client);
    this->clientContainer.remove((src));
}

void server::NetworkManager::clientConnect(clientId_t src) {
    Mutexer(this->mutex);
    clientContainer.create((src));
}

void server::NetworkManager::clientJoin(clientId_t src, gameId_t game) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get((src));
    core->setClient(client, game);
}

void server::NetworkManager::clientPlayerAttack(clientId_t src, attackId_t attackId, round_t tick) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get((src));
    if (client.getController())
        client.getController()->playShoot(attackId, tick);
}

void server::NetworkManager::clientPlayerMove(clientId_t src, speed_t vectX, speed_t vectY) {
    Mutexer(this->mutex);
    //TODO Use tick
    Client &client = this->clientContainer.get((src));
    if (client.getController())
        client.getController()->playMove(vectX, vectY);
}

void server::NetworkManager::clientPlayerQuit(clientId_t src) {
    Mutexer(this->mutex);
    Client &client = this->clientContainer.get((src));
    core->removeClient(client);
}

server::NetworkManager::ConnectionListener *server::NetworkManager::getConnectionListener() const {
    return connectionListener;
}

server::NetworkManager::DisconnectionListener *server::NetworkManager::getDisconnectionListener() const {
    return disconnectionListener;
}

void server::NetworkManager::askGame(clientId_t src) {
    Mutexer(this->mutex);
    const std::vector<Game *> &games = this->core->getGames();
    network::PacketFactory *pFactory = this->core->getPacketFactory();


    std::vector<std::pair<uint8_t, uint16_t >> serializedVector;
    for (auto game : games) {
        serializedVector.push_back(std::pair<uint8_t, uint16_t>(game->getClientSize(), game->getLobbyId()));
    }
    network::packet::PacketGameList list = network::packet::PacketGameList(serializedVector);
    pFactory->send(list, src);
}

void server::NetworkManager::askLeaderBoard(server::clientId_t src) {
    Mutexer(this->mutex);
    network::packet::PacketLeaderBoard board = network::packet::PacketLeaderBoard(std::vector<std::pair<uint32_t, std::string>>());
    this->core->getPacketFactory()->send(board, src);
}

server::NetworkManager::ConnectionListener::ConnectionListener(server::ClientContainer &clientContainer)
        : clientContainer(clientContainer) {}

void server::NetworkManager::ConnectionListener::notify(unsigned long fd) {
    std::cout << "New client: " << std::to_string(fd) << std::endl;
    this->clientContainer.create(fd);
}


/*
 * -------------------------------------------------------------------------------------------------
 */

server::NetworkManager::DisconnectionListener::DisconnectionListener(server::ClientContainer &clientContainer,
                                                                     server::Core *core)
        : clientContainer(clientContainer), core(core) {

}

void server::NetworkManager::DisconnectionListener::notify(unsigned long fd) {
    std::cout << "Client disconnected: " << std::to_string(fd) << std::endl;
    Client &client = this->clientContainer.get(fd);
    core->removeClient(client);
    this->clientContainer.remove(fd);
}

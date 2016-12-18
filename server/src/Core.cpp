
#include "Explorer/FileExplorer.hh"
#include "Core.hh"
#include <algorithm>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <cassert>
#include <listeners/ServerListenerSyn.hh>
#include <listeners/ServerListenerAck.hh>
#include <listeners/ServerListenerAskLeaderboard.hh>
#include <listeners/ServerListenerAskList.hh>
#include <listeners/ServerListenerConnect.hh>
#include <listeners/ServerListenerDisconnect.hh>
#include <listeners/ServerListenerErrorHandshake.hh>
#include <listeners/ServerListenerJoin.hh>
#include <listeners/ServerListenerPlayerAttack.hh>
#include <listeners/ServerListenerPlayerMove.hh>
#include <listeners/ServerListenerPong.hh>
#include <listeners/ServerListenerQuit.hh>
#include <listeners/ServerListenerRegister.hh>

server::Core::Core(const std::string &path, const unsigned short port)
        : sw(IStopwatch::getInstance()), packetFactory(nullptr), networkManager(
        nullptr) {
    FolderExplorer fileExplorer(path);

    lastGameId = 0;
    this->isRunning = true;
    fileExplorer.loadFolder();
    this->networkManager = new NetworkManager(this);
    const std::vector<IExplorer::File> &vector = fileExplorer.getFiles();
    for (auto f : vector) {
        if (f.name.find(".json") == std::string::npos) {
            continue;
        }
        try {
            this->levels.push_back(Level(path + f.name));
        }
        catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
    if (levels.empty()) {
        std::cerr << "No levels. Aborting." << std::endl;
        return;
    }
    this->packetFactory = new network::PacketFactory(port);
    this->packetFactory->registerConnectionListener(this->networkManager->getConnectionListener());
    this->packetFactory->registerDisconnectionListener(this->networkManager->getDisconnectionListener());
//    this->packetFactory->registerListener(new ServerListenerAck());
    this->packetFactory->registerListener(new ServerListenerAskLeaderboard());
    this->packetFactory->registerListener(new ServerListenerAskList(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerDisconnect(this->networkManager));
//    this->packetFactory->registerListener(new ServerListenerErrorHandshake());
    this->packetFactory->registerListener(new ServerListenerJoin(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerPlayerAttack());
    this->packetFactory->registerListener(new ServerListenerPlayerMove());
//    this->packetFactory->registerListener(new ServerListenerPong());
    this->packetFactory->registerListener(new ServerListenerQuit());
    this->packetFactory->registerListener(new ServerListenerRegister());
//    this->packetFactory->registerListener(new ServerListenerSyn());
}

void server::Core::run() {
    while (isRunning) {
        sw->set();
        mutex.lock();

        std::cout << "- round - - - - - - - - - - - - - - - - - -" << std::endl;
        for (auto &game : games) {
            std::cout << "- game " << std::to_string(game->getLobbyId()) << " - - -" << std::endl;
            game->tick();
        }
        mutex.unlock();

        if (sw->ellapsedMs() < ROUND_DURATION_MS)
            std::this_thread::sleep_for(std::chrono::milliseconds(ROUND_DURATION_MS - sw->ellapsedMs()));
    }
}

void server::Core::setClient(server::Client &client, server::gameId_t gameId) {
    mutex.lock();
    psetClient(client, gameId);
    mutex.unlock();
}

void server::Core::psetClient(server::Client &client, server::gameId_t gameId) {
    premoveClient(client);
    for (auto &game : games) {
        if (game->getLobbyId() == gameId) {
            game->newPlayer(&client);
            return;
        }
    }

    games.push_back(new Game(gameId));
    games.back()->setLevel(levels[lastGameId % levels.size()]);
    ++lastGameId;
    games.back()->newPlayer(&client);
}


void server::Core::removeClient(server::Client &client) {
    mutex.lock();
    premoveClient(client);
    mutex.unlock();
}

void server::Core::premoveClient(server::Client &client) {
    auto game = getClientsGame(client);
    if (game) {
        game->removePlayer(&client);
        if (game->empty()) {
            auto it = std::find(games.begin(), games.end(), game);
            delete *it;
            games.erase(it);
        }
    }
}

server::Game *server::Core::getClientsGame(const server::Client &client) {
    for (auto &game : games) {
        if (game->hasClient(client))
            return (game);
    }
    return (nullptr);
}

server::Core::Core(const std::string &path, server::NetworkManager *networkManager) : sw(IStopwatch::getInstance()),
                                                                                      packetFactory(nullptr),
                                                                                      networkManager(
                                                                                              nullptr) {
    this->networkManager = networkManager;
    FolderExplorer fileExplorer(path);

    lastGameId = 0;
    this->isRunning = true;
    fileExplorer.loadFolder();
    this->networkManager = new NetworkManager(this);
    const std::vector<IExplorer::File> &vector = fileExplorer.getFiles();
    for (auto f : vector) {
        if (f.name.find(".json") == std::string::npos) {
            continue;
        }
        try {
            this->levels.push_back(Level(path + f.name));
        }
        catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
    if (levels.empty()) {
        std::cerr << "No levels. Aborting." << std::endl;
        return;
    }
}

server::Core::~Core() {
    mutex.lock();
    mutex.unlock();
    delete sw;
    if (networkManager)
        delete networkManager;
    if (packetFactory) {
        delete packetFactory;
    }
}

const std::vector<server::Game *> &server::Core::getGames() const {
    return games;
}

network::PacketFactory *server::Core::getPacketFactory() const {
    return packetFactory;
}


#include "Explorer/FileExplorer.hh"
#include "Core.hh"
#include <algorithm>
#include <thread>
#include <iostream>
#include <cassert>
#include <listeners/ServerListenerAskLeaderboard.hh>
#include <listeners/ServerListenerAskList.hh>
#include <listeners/ServerListenerJoin.hh>
#include <listeners/ServerListenerPlayerAttack.hh>
#include <listeners/ServerListenerPlayerMove.hh>
#include <listeners/ServerListenerQuit.hh>
#include <listeners/ServerListenerRegister.hh>
#include <ProjTester.hpp>

server::Core::Core(const std::string &path, const unsigned short port)
        : sw(helpers::IStopwatch::getInstance()), packetFactory(nullptr), networkManager(nullptr)
{
    std::cout << "Instanciation" << std::endl;

    IExplorer *fileExplorer = IExplorer::getInstance();
    this->isRunning = true;
    fileExplorer->loadFolder(path);
    this->networkManager = new NetworkManager(this);

    std::cout << "Loading levels from '" << path << "'" << std::endl;
    const std::vector<IExplorer::File> &vector = fileExplorer->getFiles();
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

    std::cout << std::to_string(levels.size()) << " levels loaded" << std::endl;

    std::cout << "Preparing packet factory on port " << std::to_string(port) << std::endl;

    //this->packetFactory = new PacketFactoryTest(port);
    this->packetFactory = new network::PacketFactory(port);
    this->packetFactory->registerConnectionListener(this->networkManager->getConnectionListener());
    this->packetFactory->registerDisconnectionListener(this->networkManager->getDisconnectionListener());
    this->packetFactory->registerListener(new ServerListenerAskLeaderboard(nullptr));
    this->packetFactory->registerListener(new ServerListenerAskList(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerJoin(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerPlayerAttack(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerPlayerMove(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerQuit(this->networkManager));
    this->packetFactory->registerListener(new ServerListenerRegister(this->networkManager));
    this->packetFactory->run();

    std::cout << "Server ready" << std::endl;
}

void server::Core::run() {
    std::cout << "Server running" << std::endl;

    while (isRunning) {
        sw->set();
        mutex.lock();

        for (auto &game : games) {
            INFO("- game " << std::to_string(game->getLobbyId()) << " - - -");
            game->tick();
        }
        mutex.unlock();

        if (sw->elapsedMs() < ROUND_DURATION_MS)
            std::this_thread::sleep_for(std::chrono::milliseconds(ROUND_DURATION_MS - sw->elapsedMs()));
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

    games.push_back(new Game(*packetFactory, gameId));
    games.back()->setLevel(levels[gameId % levels.size()]);
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

server::Core::Core(const std::string &path, server::NetworkManager *networkManager) : sw(helpers::IStopwatch::getInstance()),
                                                                                      packetFactory(nullptr),
                                                                                      networkManager(
                                                                                              nullptr) {
    this->networkManager = networkManager;
    IExplorer *fileExplorer = IExplorer::getInstance();

    this->isRunning = true;
    fileExplorer->loadFolder(path);
    this->networkManager = new NetworkManager(this);
    const std::vector<IExplorer::File> &vector = fileExplorer->getFiles();
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
    this->packetFactory = new PacketFactoryNoNetwork(6000);
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

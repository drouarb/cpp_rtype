
#include "Explorer/FileExplorer.hh"
#include "Core.hh"
#include <algorithm>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <cassert>

server::Core::Core(const std::string &path) : sw() {
    FolderExplorer fileExplorer(path);

    lastGameId = 0;
    this->isRunning = true;
    fileExplorer.loadFolder();
    this->max = 0;
    this->networkManager = new NetworkManager(this);
    const std::vector<IExplorer::File> &vector = fileExplorer.getFiles();
    for (auto f : vector) {
        if (f.name.find(".json") == std::string::npos) {
            continue;
        }
        try {
            this->levels.push_back(Level(path + f.name));
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
        catch (std::exception &e) {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (levels.empty()) {
        std::cerr << "No levels. Aborting." << std::endl;
        return;
    }
}

void server::Core::run() {
    round_t r;
    while (this->isRunning) {
        sw.set();
        mutex.lock();
        std::cout << "- round " << std::to_string(r) << " - - - - - - - - - - - - - - - - - -" << std::endl;
        for (auto &game : games) {
            std::cout << "- game " << std::to_string(game->getLobbyId()) << " - - -" << std::endl;
            game->tick(r);
        }
        ++r;
        mutex.unlock();
        usleep(ROUND_DURATION_MS - sw.ellapsedMs());
        if (max && r >= max) {
            return;
        }
    }
}

void server::Core::setClient(server::Client &client, server::gameId_t gameId) {
    removeClient(client);
    for (auto &game : games) {
        if (game->getLobbyId() == gameId) {
            game->newPlayer(&client);
            return;
        }
    }

    games.push_back(new Game(lastGameId));
    games.back()->setLevel(levels[lastGameId % levels.size()]);
    games.back()->newPlayer(&client);
    assert(client.getController() != nullptr);
    ++lastGameId; //TODO strange
}

void server::Core::removeClient(server::Client &client) {
    auto game = getClientsGame(client);
    if (game) {
        game->removePlayer(&client);
        if (game->empty()) {
            games.erase(std::find(games.begin(), games.end(), game));
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

server::Core::Core(const std::string &path, server::NetworkManager *networkManager) : Core(path) {
    delete (this->networkManager);
    this->networkManager = networkManager;
}
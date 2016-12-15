
#include "Explorer/FileExplorer.hh"
#include "Core.hh"
#include <algorithm>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <cassert>

server::Core::Core(const std::string &path) : sw(IStopwatch::getInstance())
{
    FolderExplorer fileExplorer(path);

    lastGameId = 0;
    this->isRunning = true;
    fileExplorer.loadFolder();
    this->networkManager = new NetworkManager(this);
    const std::vector<IExplorer::File> &vector = fileExplorer.getFiles();
    for (auto f : vector)
    {
        if (f.name.find(".json") == std::string::npos)
        {
            continue;
        }
        try
        {
            this->levels.push_back(Level(path + f.name));
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
    if (levels.empty())
    {
        std::cerr << "No levels. Aborting." << std::endl;
        return;
    }
}

void server::Core::run()
{
    //round_t r = 0;
    while (isRunning)
    {
/*
        if (r == 2)
        {
            networkManager->clientConnect(14);
            ++r;
        }
        if (r == 6)
        {
            networkManager->clientJoin(14, 2);
            ++r;
        }
        if (r == 9)
        {
            networkManager->clientPlayerAttack(14, 8, 0);
            networkManager->clientPlayerMove(14, 3, 0);
            ++r;
        }
        if (r == 12)
        {
            ++r;
        }
        if (r == 14)
        {
            networkManager->clientJoin(14, 3);
            ++r;
        }
        if (r == 20)
        {
            networkManager->clientDisconnect(14);
            ++r;
        }
        if (r == 22)
            return;
        ++r;
*/


        sw->set();
        mutex.lock();

        std::cout << "- round  - - - - - - - - - - - - - - - - - -" << std::endl;
        for (auto &game : games)
        {
            std::cout << "- game " << std::to_string(game->getLobbyId()) << " - - -" << std::endl;
            game->tick();
        }
        mutex.unlock();

        if (sw->ellapsedMs() < ROUND_DURATION_MS)
            usleep((ROUND_DURATION_MS - sw->ellapsedMs()) * 1000);
    }
}

void server::Core::setClient(server::Client &client, server::gameId_t gameId)
{
    mutex.lock();
    psetClient(client, gameId);
    mutex.unlock();
}

void server::Core::psetClient(server::Client &client, server::gameId_t gameId)
{
    premoveClient(client);
    for (auto &game : games)
    {
        if (game->getLobbyId() == gameId)
        {
            game->newPlayer(&client);
            return;
        }
    }

    games.push_back(new Game(gameId));
    games.back()->setLevel(levels[lastGameId % levels.size()]);
    ++lastGameId;
    games.back()->newPlayer(&client);
}


void server::Core::removeClient(server::Client &client)
{
    mutex.lock();
    premoveClient(client);
    mutex.unlock();
}

void server::Core::premoveClient(server::Client &client)
{
    auto game = getClientsGame(client);
    if (game)
    {
        game->removePlayer(&client);
        if (game->empty())
        {
            auto it = std::find(games.begin(), games.end(), game);
            delete *it;
            games.erase(it);
        }
    }
}

server::Game *server::Core::getClientsGame(const server::Client &client)
{
    for (auto &game : games)
    {
        if (game->hasClient(client))
            return (game);
    }
    return (nullptr);
}

server::Core::Core(const std::string &path, server::NetworkManager *networkManager) : Core(path)
{
    delete (this->networkManager);
    this->networkManager = networkManager;
}

server::Core::~Core()
{
    mutex.lock();
    mutex.unlock();
    delete sw;
    if (networkManager)
        delete networkManager;
}
#ifndef RTYPE_SERVER_CORE_HH_
#define RTYPE_SERVER_CORE_HH_

#include "NetworkManager.hh"
#include "helpers/Stopwatch.hh"
#include <string>
#include <Level.hh>
#include <Game.hh>
#include <mutex>

namespace server {

    class NetworkManager;

    class Core {
    private:
        NetworkManager *networkManager;
        std::mutex mutex;
        std::vector<Level> levels;
        std::vector<Game> games;
        gameId_t lastGameId;
        Stopwatch sw;

    public:
        /**
         *
         * @param path to a folder
         */
        Core(const std::string &path);

        void setClient(Client &, gameId_t);
        void removeClient(Client &);

    private:
        void run();

        Game * getClientsGame(const Client &);
    };

}

#endif
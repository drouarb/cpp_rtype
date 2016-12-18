#ifndef RTYPE_SERVER_CORE_HH_
#define RTYPE_SERVER_CORE_HH_

#include "NetworkManager.hh"
#include "helpers/IStopwatch.hh"
#include <string>
#include <Level.hh>
#include <Game.hh>
#include <mutex>
#include <network/PacketFactory.hh>

namespace server
{

    class NetworkManager;

    class Core
    {
    private:
        NetworkManager *networkManager;
        network::PacketFactory *packetFactory;
        std::mutex mutex;
        std::vector<Level> levels;
        std::vector<Game *> games;
        gameId_t lastGameId;
        IStopwatch * sw;

    protected:
        bool isRunning;

    public:
        /**
         *
         * @param path to a folder
         */
        Core(const std::string &path, const unsigned short port);
        ~Core();


        virtual void setClient(Client &, gameId_t);

        virtual void removeClient(Client &);

        virtual void run();

        const std::vector<Game *> &getGames() const;

        network::PacketFactory *getPacketFactory() const;

        /**
         *      ______                 _                _
         *     / _____)           _   (_)              | |
         *    | /      ____ _   _| |_  _  ___  ____    | |
         *    | |     / _  | | | |  _)| |/ _ \|  _ \   |_|
         *    | \____( ( | | |_| | |__| | |_| | | | |   _
         *     \______)_||_|\____|\___)_|\___/|_| |_|  |_|
         *
         *
         *
         * Test method, don't use it
         */

        Core(const std::string &path, NetworkManager *networkManager);

    private:

        Game * getClientsGame(const Client &);
        virtual void psetClient(Client &, gameId_t);
        virtual void premoveClient(Client &);
    };

}

#endif
//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_IGAMECLIENT_HH
#define CPP_RTYPE_IGAMECLIENT_HH

#include <mutex>
#include "NetworkManager.hh"
namespace client {

    class NetworkManager;
    class GameClient {
    private:
        std::mutex client_mut;
        NetworkManager *manager  = NULL;
    public:
        GameClient();
        ~GameClient(){};
        void createNetworkManager(const std::string &ip, unsigned short port);
        void deleteNetworkManager();
    };
}

#endif //CPP_RTYPE_IGAMECLIENT_HH

//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_IGAMECLIENT_HH
#define CPP_RTYPE_IGAMECLIENT_HH

#include <mutex>
#include "networkManager.hh"
namespace client {

    class GameClient {
    private:
        std::mutex client_mut;
        networkManager *manager  = NULL;
    public:
        GameClient();
        ~GameClient(){};
        void createNetworkManager(const std::string &ip, unsigned short port);
        void deleteNetworkManager();
    };
}

#endif //CPP_RTYPE_IGAMECLIENT_HH

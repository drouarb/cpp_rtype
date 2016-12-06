//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_IGAMECLIENT_HH
#define CPP_RTYPE_IGAMECLIENT_HH

#include "networkManager.hh"
#include <mutex>
#include <utility>

#define WAIT_SERVER 1
typedef std::chrono::high_resolution_clock Clock;
namespace client {

    class GameClient {
    private:
        std::mutex client_mut;
        std::pair<uint16_t , uint16_t>syn_ack = std::pair<uint16_t , uint16_t>(UINT16_MAX, UINT16_MAX);
        bool error_hanshake = false;
        networkManager *manager  = NULL;
    public:
        GameClient();
        ~GameClient(){};
        void createNetworkManager(const std::string &ip, unsigned short port);
        void deleteNetworkManager();
        bool Handshake();
        void SynAckValidation(uint16_t syn, uint16_t ack);
        void HandshakeErroFromServer(const std::string &message);
    };
}

#endif //CPP_RTYPE_IGAMECLIENT_HH

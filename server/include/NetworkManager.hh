#pragma once

#include <list>
#include <map>
#include <listeners/IListenerHandler.hh>
#include <helpers/ClientContainer.hh>
#include "Client.hh"

namespace server {
    class NetworkManager : public server::IListenerHandler {
        ClientContainer clientContainer;
    public:
        const std::list<Client> &getClientList() const;

        void sendGameState(int hp, clientId_t clientId);

        void sendMessage(const std::string &msg, clientId_t clientId);

        void clientRegister(int src, const std::string &name) override;

        void clientDisconnect(int src) override;

        void clientJoin(int src) override;

        void clientPlayerAttack(int src) override;

        void clientPlayerMove(int src) override;

        void clientPlayerQuit(int src) override;
    };
}
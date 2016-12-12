#pragma once

#include <list>
#include <map>
#include <listeners/IListenerHandler.hh>
#include <helpers/ClientContainer.hh>
#include "definitions.hh"
#include "Client.hh"
#include "Core.hh"

namespace server {

    class Core;

    class NetworkManager : public server::IListenerHandler {
    protected:
        ClientContainer clientContainer;
        Core *core;
    public:
        NetworkManager(Core *core);

        void createClient(int src) override;

        const std::list<Client> &getClientList() const;

        void sendGameState(int hp, clientId_t clientId);

        void sendMessage(const std::string &msg, clientId_t clientId);

        void clientRegister(int src, const std::string &name) override;

        void clientDisconnect(int src) override;

        void clientConnect(int src);

        void clientJoin(int src, gameId_t game) override;

        void clientPlayerAttack(int src, attackId_t attackId, round_t tick) override;

        void clientPlayerMove(int src, uint16_t vectX, uint16_t vectY) override;

        void clientPlayerQuit(int src) override;
    };
}
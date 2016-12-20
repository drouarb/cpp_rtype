#pragma once

#include <list>
#include <map>
#include <listeners/IListenerHandler.hh>
#include "network/listener/ISocketConnectionListener.hh"
#include "network/listener/ISocketDisconnectionListener.hh"
#include <helpers/ClientContainer.hh>
#include <thread/IMutex.hh>
#include "Definitions.hh"
#include "Client.hh"
#include "Core.hh"

namespace server {

    class Core;

    class NetworkManager : public server::IListenerHandler {
    protected:
        ClientContainer clientContainer;
        Core *core;
    private:
        IMutex *mutex;

        class ConnectionListener : public network::listener::ISocketConnectionListener {
        private:
            ClientContainer &clientContainer;
        public:
            ConnectionListener(ClientContainer &clientContainer);

            void notify(unsigned long fd) override;
        };

        class DisconnectionListener : public network::listener::ISocketDisconnectionListener {
        private:
            ClientContainer &clientContainer;
            server::Core *core;
        public:
            DisconnectionListener(server::ClientContainer &clientContainer, server::Core *core);

            void notify(unsigned long fd) override;
        };


        ConnectionListener      *connectionListener;
        DisconnectionListener   *disconnectionListener;

    public:

        NetworkManager(Core *core);

        virtual ~NetworkManager();

        const std::list<Client> &getClientList() const;

        void sendGameState(int hp, clientId_t clientId);

        void sendMessage(const std::string &msg, clientId_t clientId);

        void clientRegister(clientId_t src, const std::string &name) override;

        void clientDisconnect(clientId_t src) override;

        void clientConnect(clientId_t src);

        void clientJoin(clientId_t src, gameId_t game) override;

        void clientPlayerAttack(clientId_t src, attackId_t attackId, round_t tick) override;

        void clientPlayerMove(clientId_t src, speed_t vectX, speed_t vectY) override;

        void clientPlayerQuit(clientId_t src) override;

        void askGame(clientId_t src) override;

        ConnectionListener *getConnectionListener() const;

        DisconnectionListener *getDisconnectionListener() const;
    };
}
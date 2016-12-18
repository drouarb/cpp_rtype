#pragma once

#include <list>
#include <map>
#include <listeners/IListenerHandler.hh>
#include "network/listener/ISocketConnectionListener.hh"
#include "network/listener/ISocketDisconnectionListener.hh"
#include <helpers/ClientContainer.hh>
#include <thread/IMutex.hh>
#include "definitions.hh"
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
        public:
            DisconnectionListener(server::ClientContainer &clientContainer);

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

        void clientRegister(int src, const std::string &name) override;

        void clientDisconnect(int src) override;

        void clientConnect(int src);

        void clientJoin(int src, gameId_t game) override;

        void clientPlayerAttack(int src, attackId_t attackId, round_t tick) override;

        void clientPlayerMove(int src, speed_t vectX, speed_t vectY) override;

        void clientPlayerQuit(int src) override;

        void askGame(int src) override;

        ConnectionListener *getConnectionListener() const;

        DisconnectionListener *getDisconnectionListener() const;
    };
}
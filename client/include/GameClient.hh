//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_GAMECLIENT_HH
#define CPP_RTYPE_GAMECLIENT_HH

#include <utility>
#include <mutex>
#include "World.hh"
#include "Entity.hh"
#include "NetworkManager.hh"
#include "Definitions.hh"
#include "UI/UIManager.hh"

#define TICKRATE 60

namespace client {
    class NetworkManager;

    class GameClient {
    private:
        NetworkManager *manager;
        tick tickRateServer;
        World *world;
        UI::UIManager managerUi;
        IEventHandler *handler;
    public:
        World *getWorld() const;

    private:
        std::map<tick, uint64_t> horodatageTick;
    public:
        GameClient();

        ~GameClient() {};
        void manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId,
                                uint16_t pos_x, uint16_t pos_y);

        void manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t hp);

        void createNetworkManager(const std::string &ip, unsigned short port);

        void deleteNetworkManager();

        void gameLoop();
        UI::UIManager *getUi(){
            return &this->managerUi;
        }

        void manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t vecx, uint16_t vecy);
        void manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId);
    private:
        void readaptTickRate(int servTickRate,
                             std::pair<tick, uint64_t> estiClientHoro,
                             std::pair<tick, uint64_t> servHoro);

        int calcTickRate(int nbrLevel);
    };
}

#endif //CPP_RTYPE_GAMECLIENT_HH

//
// Created by celeriy on 29/11/16.
//

#ifndef CPP_RTYPE_NETWORKMANAGER_HH
#define CPP_RTYPE_NETWORKMANAGER_HH

#include <network/PacketFactory.hh>
#include <vector>
#include "GameClient.hh"

namespace client {
    class GameClient;

    class NetworkManager {
    private:
        GameClient *gameClient = nullptr;
        network::PacketFactory *packetFactory = nullptr;
        std::vector<network::listener::IPacketListener *> listeners;
    public:
        ~NetworkManager();

        network::PacketFactory *getPacketFactory() const;

        NetworkManager(const std::string &ip, unsigned short port, GameClient *gameclient);

        void addListenerToPacketFactory();

        bool startPacketFactory();

        void receiveDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId);

        void receiveDisconnect();

        void receiveCancelEvent(uint32_t eventId);

        void receiveErrorList(const std::string &message);

        void receiveEventError(const std::string &message);

        void receiveGameList(const std::vector<std::pair<uint8_t, uint16_t >> GameList);

        void receiveLeaderBoard(std::vector<std::pair<uint32_t, std::string>> LeaderBoard);

        void receiveMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t vecx, uint16_t vecy);

        void receivePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName);

        void receiveQuit();

        void receiveSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId,
                                uint16_t pos_x, uint16_t pos_y);

        void receiveUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t hp);

        void sendRegister(const std::string & name);

        void sendDisconnect();

        void sendAskList();

        void sendJoin(uint8_t roomId);

        void sendQuit();
        
        void sendPlayerMove(uint32_t tick , uint16_t vect_x , uint16_t vect_y);

        void sendPlayerAttack(int32_t tick, uint8_t attackId);
    };
}


#endif //CPP_RTYPE_NETWORKMANAGER_HH

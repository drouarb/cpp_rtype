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
        GameClient *gameClient;
        network::PacketFactory *packetFactory;
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

        void receiveGameList(const std::vector<std::pair<uint8_t, uint16_t > > GameList);

        void receiveLeaderBoard(std::vector<std::pair<uint32_t, std::string> > LeaderBoard);

        void receiveSyncro(uint32_t tick, int64_t time);

      void receivePlayerData(uint16_t playerId, uint8_t nbAttack);

        void receiveMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t vecx, int16_t vecy,
                                       int16_t posx, int16_t posy);

        void receivePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName);

        void receiveQuit();

        void
        receiveSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId, int16_t pos_x,
                                   int16_t pos_y, int16_t hp);

        void receiveUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp);

        void receiveGameData();
      
        void sendRegister(const std::string & name);

        void sendDisconnect();

        void sendAskList();

        void sendJoin(uint8_t roomId);

        void sendQuit();
        
        void sendPlayerMove(uint32_t tick, int16_t vect_x, int16_t vect_y, int16_t pos_x, int16_t pos_y);

        void sendPlayerAttack(int32_t tick, uint8_t attackId);
    };
}


#endif //CPP_RTYPE_NETWORKMANAGER_HH

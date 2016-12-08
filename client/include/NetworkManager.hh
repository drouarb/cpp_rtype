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
         network::PacketFactory *packetFactory = NULL;
         std::vector<network::listener::IPacketListener*>	listeners;
     public:
         ~NetworkManager();

         network::PacketFactory *getPacketFactory() const;

         NetworkManager(const std::string &ip, unsigned short port, GameClient *gameclient);

         void addListenerToPacketFactory();
         bool startPacketFactory();
     };
}


#endif //CPP_RTYPE_NETWORKMANAGER_HH

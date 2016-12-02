//
// Created by celeriy on 29/11/16.
//

#ifndef CPP_RTYPE_NETWORKMANAGER_HH
#define CPP_RTYPE_NETWORKMANAGER_HH

#include <network/PacketFactory.hh>
#include "IGameClient.hh"
namespace client {
     class networkManager {
     private:
         network::PacketFactory *packetFactory = NULL;
         std::vector<network::listener::IPacketListener*>	listeners;
     public:
         ~networkManager();

         network::PacketFactory *getPacketFactory() const;

         networkManager(const std::string &ip, unsigned short port);

         void addListenerToPacketFactory(client::IGameClient *gameclient);
         bool startPacketFactory();
     };
}


#endif //CPP_RTYPE_NETWORKMANAGER_HH

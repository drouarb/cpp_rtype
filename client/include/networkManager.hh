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
     class networkManager {
     private:
         network::PacketFactory *packetFactory = NULL;
         std::vector<network::listener::IPacketListener*>	listeners;
     public:
         ~networkManager();

         network::PacketFactory *getPacketFactory() const;

         networkManager(const std::string &ip, unsigned short port);

         void addListenerToPacketFactory(client::GameClient *gameclient);
         bool startPacketFactory();
         bool sendSyn(uint16_t syn);
         bool sendAck(uint16_t ack_value);
         bool sendErrorHandshake(const std::string & message);
     };
}


#endif //CPP_RTYPE_NETWORKMANAGER_HH
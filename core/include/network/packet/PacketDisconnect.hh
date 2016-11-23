//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETDISCONNECT_HH
#define CPP_RTYPE_PACKETDISCONNECT_HH


#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketDisconnect  : public APacket{
     public:
         PacketDisconnect();
         virtual ~PacketDisconnect();
     };
 }
}


#endif //CPP_RTYPE_PACKETDISCONNECT_HH

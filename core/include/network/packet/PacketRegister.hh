//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETREGISTER_HH
#define CPP_RTYPE_PACKETREGISTER_HH

#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketRegister : public APacket {
     public:
         PacketRegister(const std::string & message = "");
         virtual ~PacketRegister();
         const utils::NetworkString &getMessage() const;
         void setMessage(const std::string &msg);

     };
 }
}

#endif //CPP_RTYPE_PACKETREGISTER_HH

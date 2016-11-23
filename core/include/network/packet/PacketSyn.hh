//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETSYN_HH
#define CPP_RTYPE_PACKETSYN_HH

#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketSyn : public APacket {
     public:
         PacketSyn(uint16_t syn = 0);
         virtual ~PacketSyn();
         void setSyn(uint16_t syn);
        uint16_t getSyn() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETSYN_HH

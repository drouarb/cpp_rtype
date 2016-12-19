/*
** trouve_b
*/

#ifndef CPP_RTYPE_PACKETPLAYERDATA_HH
#define CPP_RTYPE_PACKETPLAYERDATA_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketPlayerData : public APacket {
        public:
            PacketPlayerData(uint16_t playerId = 0, uint8_t nbAttack = 0);
            virtual ~PacketPlayerData();
	  
            void setPlayerId(uint16_t id);
            uint16_t  getPlayerId() const;
	    void setNbAttack(uint8_t nb);
	    uint8_t getNbAttack() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETSYNCRONISATION_HH

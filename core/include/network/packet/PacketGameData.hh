//
// Created by drouar_b on 12/30/16.
//

#ifndef CPP_RTYPE_PACKETGAMEDATA_HH
#define CPP_RTYPE_PACKETGAMEDATA_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketGameData: public APacket {
        public:
            PacketGameData(const std::string &audio = "", const std::string &background = "");

            virtual ~PacketGameData();

            void setAudio(const std::string &audio);
            const std::string &getAudio() const;

            void setBackground(const std::string &background);
            const std::string &getBackground() const;
        };
    }
}

#endif //CPP_RTYPE_PACKETGAMEDATA_HH

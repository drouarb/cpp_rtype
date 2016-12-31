//
// Created by drouar_b on 12/30/16.
//

#include <network/packet/PacketGameData.hh>

network::packet::PacketGameData::PacketGameData(const std::string &audio, const std::string &background):
    APacket(
            GAME_DATA,
            {
                    new utils::NetworkString(audio.c_str()),
                    new utils::NetworkString(background.c_str())
            }
    )
{ }

network::packet::PacketGameData::~PacketGameData()
{ }

void network::packet::PacketGameData::setAudio(const std::string &audio) {
    SET_NETSTR(schema, 0, audio);
}

const std::string &network::packet::PacketGameData::getAudio() const {
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketGameData::setBackground(const std::string &background) {
    SET_NETSTR(schema, 1, background);
}

const std::string &network::packet::PacketGameData::getBackground() const {
    return GET_NETSTR(schema, 1);
}

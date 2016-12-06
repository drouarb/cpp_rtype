//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketErrorScore.hh"

network::packet::PacketErrorScore::~PacketErrorScore()
{

}

network::packet::PacketErrorScore::PacketErrorScore(const std::string &message) :
        APacket(
                ERROR_SCORE,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketErrorScore::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketErrorScore::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}

//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketErrorGame.hh"

network::packet::PacketErrorGame::~PacketErrorGame()
{

}

network::packet::PacketErrorGame::PacketErrorGame(const std::string &message) :
        APacket(
                ERROR_GAME,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketErrorGame::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketErrorGame::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}

//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketErrorHandshake.hh"

network::packet::PacketErrorHandshake::~PacketErrorHandshake()
{

}

network::packet::PacketErrorHandshake::PacketErrorHandshake(const std::string &message) : APacket(
        ERROR_HANDSHAKE,
        {
                new utils::NetworkString(message.c_str())
        }
)
{}

const network::utils::NetworkString &network::packet::PacketErrorHandshake::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketErrorHandshake::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}

//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketPing.hh"

network::packet::PacketPing::~PacketPing()
{

}

network::packet::PacketPing::PacketPing(const std::string &message) :
        APacket(
                PING,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketPing::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketPing::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}

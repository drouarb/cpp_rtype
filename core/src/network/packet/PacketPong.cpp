//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketPong.hh"
network::packet::PacketPong::~PacketPong()
{

}

network::packet::PacketPong::PacketPong(const std::string &message) :
        APacket(
                PONG,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketPong::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketPong::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}



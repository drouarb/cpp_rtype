//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketRegister.hh"

network::packet::PacketRegister::~PacketRegister()
{

}

network::packet::PacketRegister::PacketRegister(const std::string &message) :
        APacket(
                REGISTER,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketRegister::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketRegister::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}

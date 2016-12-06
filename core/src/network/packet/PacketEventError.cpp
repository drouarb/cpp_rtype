//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketEventError.hh"

network::packet::PacketEventError::~PacketEventError()
{

}

network::packet::PacketEventError::PacketEventError(const std::string &message) :
        APacket(
                EVENT_ERROR,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketEventError::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketEventError::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}



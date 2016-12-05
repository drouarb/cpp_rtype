//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketErrorList.hh"

network::packet::PacketErrorList::~PacketErrorList()
{

}

network::packet::PacketErrorList::PacketErrorList(const std::string &message) :
        APacket(
                ERROR_LIST,
                {
                        new utils::NetworkString(message.c_str())
                }
        )
{}

const network::utils::NetworkString &network::packet::PacketErrorList::getMessage() const
{
    return GET_NETSTR(schema, 0);
}

void network::packet::PacketErrorList::setMessage(const std::string &msg)
{
    SET_NETSTR(schema, 0, msg);
}

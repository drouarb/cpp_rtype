//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerSynAck.hh"
using namespace client;
ClientListenerSynAck::ClientListenerSynAck(GameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::SYN_ACK)
{

}

ClientListenerSynAck::~ClientListenerSynAck()
{

}

void ClientListenerSynAck::notify(const network::packet::PacketSynAck *packet)
{
    gameclient->SynAckValidation(packet->getSyn(),packet->getAck());
}

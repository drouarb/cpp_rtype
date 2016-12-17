//
// Created by celeriy on 05/12/16.
//

#include "listener/ClientListenerErrorHandShake.hh"


using namespace client;
ClientListenerErrorHandShake::ClientListenerErrorHandShake(client::GameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::ERROR_HANDSHAKE)
{

}

ClientListenerErrorHandShake::~ClientListenerErrorHandShake()
{

}

void ClientListenerErrorHandShake::notify(const network::packet::PacketErrorHandshake *packet)
{
    gameclient->HandshakeErroFromServer(packet->getMessage());
}

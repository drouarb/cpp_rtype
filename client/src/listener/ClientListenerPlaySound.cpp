//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerPlaySound.hh"
using namespace client;

ClientListenerPlaySound::ClientListenerPlaySound(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::PLAY_SOUND)
{

}

ClientListenerPlaySound::~ClientListenerPlaySound()
{

}

void ClientListenerPlaySound::notify(const network::packet::PacketPlaySound *packet)
{

}
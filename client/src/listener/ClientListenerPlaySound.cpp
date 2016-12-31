//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerPlaySound.hh"
using namespace client;

ClientListenerPlaySound::ClientListenerPlaySound(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::PLAY_SOUND)
{

}

ClientListenerPlaySound::~ClientListenerPlaySound()
{

}

void ClientListenerPlaySound::notify(const network::packet::PacketPlaySound *packet)
{
    networkManager->receivePlaySound(packet->getTick(),packet->getEventId(), packet->getSoundName());
}
//
// Created by celeriy on 29/11/16.
//

#include <stdexcept>
#include <network/packet/PacketSyn.hh>
#include <listener/ClientListenerCancelEvent.hh>
#include <listener/ClientListenerDeleteEntity.hh>
#include <listener/ClientListenerDisconnect.hh>
#include <listener/ClientListenerErrorList.hh>
#include <listener/ClientListenerEventError.hh>
#include <listener/ClientListenerGameList.hh>
#include <listener/ClientListenerLeaderBoard.hh>
#include <listener/ClientListenerMoveEntity.hh>
#include <listener/ClientListenerPlaySound.hh>
#include <listener/ClientListenerQuit.hh>
#include <listener/ClientListenerSpawnEntity.hh>
#include <listener/ClientListenerUpdateEntity.hh>
#include <iostream>
#include <network/packet/PacketAck.hh>
#include "networkManager.hh"

using namespace client;

networkManager::~networkManager()
{
    delete(packetFactory);
}

networkManager::networkManager(const std::string &ip, unsigned short port)
{
    try
    {
        this->packetFactory =  new network::PacketFactory(ip, port);
    }
    catch (std::runtime_error & e)
    {
        this->packetFactory = NULL;
        std::cerr << e.what() << std::endl;
        throw (std::runtime_error("netWorkManager failed to instance"));
    }
}

network::PacketFactory *networkManager::getPacketFactory() const
{
    return packetFactory;
}

bool networkManager::startPacketFactory()
{
    try {
        if (packetFactory == NULL)
            return false;
        packetFactory->run();
    }
    catch (std::exception & e)
    {
        throw (new std::runtime_error(e.what()));
    }
    return true;
}

void networkManager::addListenerToPacketFactory(client::GameClient *gameclient)
{
    listeners.push_back(new client::ClientListenerCancelEvent(gameclient));
    listeners.push_back(new client::ClientListenerDeleteEntity(gameclient));
    listeners.push_back(new client::ClientListenerDisconnect(gameclient));
    listeners.push_back(new client::ClientListenerErrorList(gameclient));
    listeners.push_back(new client::ClientListenerEventError(gameclient));
    listeners.push_back(new client::ClientListenerGameList(gameclient));
    listeners.push_back(new client::ClientListenerLeaderBoard(gameclient));
    listeners.push_back(new client::ClientListenerMoveEntity(gameclient));
    listeners.push_back(new client::ClientListenerPlaySound(gameclient));
    listeners.push_back(new client::ClientListenerQuit(gameclient));
    listeners.push_back(new client::ClientListenerSpawnEntity(gameclient));
    listeners.push_back(new client::ClientListenerUpdateEntity(gameclient));
    for (auto it = listeners.begin(); it != listeners.end(); it++)
        packetFactory->registerListener(*it);
}


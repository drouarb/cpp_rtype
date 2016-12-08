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
#include "NetworkManager.hh"

using namespace client;

NetworkManager::~NetworkManager()
{
    delete(packetFactory);
}

NetworkManager::NetworkManager(const std::string &ip, unsigned short port, GameClient *gameclient) : gameClient(gameclient)
{
    try
    {
        this->packetFactory =  new network::PacketFactory(ip, port);
    }
    catch (std::runtime_error & e)
    {
        this->packetFactory = nullptr;
        std::cerr << e.what() << std::endl;
        throw (std::runtime_error("netWorkManager failed to instance"));
    }
}

network::PacketFactory *NetworkManager::getPacketFactory() const
{
    return packetFactory;
}

bool NetworkManager::startPacketFactory()
{
    try {
        if (packetFactory == nullptr)
            return false;
        packetFactory->run();
    }
    catch (std::exception & e)
    {
        throw (new std::runtime_error(e.what()));
    }
    return true;
}

void NetworkManager::addListenerToPacketFactory()
{
    listeners.push_back(new client::ClientListenerCancelEvent(this));
    listeners.push_back(new client::ClientListenerDeleteEntity(this));
    listeners.push_back(new client::ClientListenerDisconnect(this));
    listeners.push_back(new client::ClientListenerErrorList(this));
    listeners.push_back(new client::ClientListenerEventError(this));
    listeners.push_back(new client::ClientListenerGameList(this));
    listeners.push_back(new client::ClientListenerLeaderBoard(this));
    listeners.push_back(new client::ClientListenerMoveEntity(this));
    listeners.push_back(new client::ClientListenerPlaySound(this));
    listeners.push_back(new client::ClientListenerQuit(this));
    listeners.push_back(new client::ClientListenerSpawnEntity(this));
    listeners.push_back(new client::ClientListenerUpdateEntity(this));
    for (auto it = listeners.begin(); it != listeners.end(); it++)
        packetFactory->registerListener(*it);
}


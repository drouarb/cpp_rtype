//
// Created by celeriy on 28/11/16.
//

#include <stdexcept>
#include <iostream>
#include "GameClient.hh"
#include <future>

client::GameClient::GameClient()
{
}

void client::GameClient::createNetworkManager(const std::string &ip, unsigned short port)
{
    try
    {
        manager = new networkManager(ip, port);
        manager->addListenerToPacketFactory(this);
        manager->startPacketFactory();
    }
    catch (std::runtime_error &e)
    {
        manager = NULL;
        std::cerr << e.what() << std::endl;

    }
}

void client::GameClient::deleteNetworkManager()
{
    delete (manager);
    manager = NULL;
}

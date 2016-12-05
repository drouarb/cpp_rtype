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

bool client::GameClient::Handshake()
{
    syn_ack.first = UINT16_MAX;

    uint16_t syn = rand() % (UINT16_MAX - 1);
    if (manager == NULL)
        return false;
    manager->sendSyn(syn);
    auto t = Clock::now();
    while (syn_ack.first == UINT16_MAX)
    {
        if (error_hanshake == true ||
            std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t).count() > WAIT_SERVER)
        {
            error_hanshake = false;
            return false;
        }
    }
    if (syn_ack.second != (syn + 1))
    {
        this->manager->sendErrorHandshake("ack different from syn + 1");
        std::cerr << "ack different to syn + 1  ack = " << syn_ack.second << "  syn = " << syn << std::endl;
        return (false);
    }
    manager->sendAck(syn_ack.first + 1);
    t = Clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t).count() > WAIT_SERVER)
    {
        if (error_hanshake == true)
        {
            error_hanshake = false;
            return false;
        }
    }
    return (true);
}

void client::GameClient::SynAckValidation(uint16_t syn, uint16_t ack)
{
    syn_ack.first = syn;
    syn_ack.second = ack;
}

void client::GameClient::HandshakeErroFromServer(const std::string &message)
{
    this->error_hanshake = true;
    std::cerr << message << std::endl;
}

//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerDisconnect.hh"

using namespace client;
ClientListenerDisconnect::ClientListenerDisconnect(NetworkManager *networkManager) :  networkManager(networkManager)
{
}

ClientListenerDisconnect::~ClientListenerDisconnect()
{

}

void ClientListenerDisconnect::notify(unsigned long fd)
{
  std::cout << "receive real disco" << std::endl;
    networkManager->receiveDisconnect();
}

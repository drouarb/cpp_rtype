//
// Created by celeriy on 28/11/16.
//

#include <stdexcept>
#include <iostream>
#include <future>
#include "GameClient.hh"

using namespace client;

client::GameClient::GameClient()
{
  manager = NULL;
  tickRateServer = TICKRATE;
}

void client::GameClient::createNetworkManager(const std::string &ip, unsigned short port)
{
    try
    {
        manager = new NetworkManager(ip, port, this);
        manager->addListenerToPacketFactory();
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

void	GameClient::gameLoop()
{
  
}

void	GameClient::readaptTickRate(int servTickRate,
				    std::pair<tick, uint64_t> estiClientHoro,
				    std::pair<tick, uint64_t> servHoro)
{
  // ici faire une formule pour gérer le tickrate et le réadapter sur le rythme du serveur
}

int	GameClient::calcTickRate(int nbrLevel)
{
  std::map<tick, uint64_t>::iterator it;
  tick					tickBegin;
  uint64_t				timeBegin;
  tick					tickEnd;
  uint64_t				timeEnd;

  it = horodatageTick.end();
  --it;
  tickBegin = it->first;
  timeBegin = it->second;
  while (nbrLevel > 0 && it != horodatageTick.begin())
    {
      --it;
      --nbrLevel;
    }
  tickEnd = it->first;
  timeEnd = it->second;
  return ((tickBegin - tickEnd) / ((timeBegin - timeEnd) * 1000));
}

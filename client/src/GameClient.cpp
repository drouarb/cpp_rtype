//
// Created by celeriy on 28/11/16.
//

#include <stdexcept>
#include <iostream>
#include <future>
#include "GameClient.hh"

using namespace client;

client::GameClient::GameClient() :manager(nullptr) , tickRateServer(TICKRATE), world(nullptr)
{
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
        manager = nullptr;
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

World *GameClient::getWorld() const {
    return world;
}

void GameClient::manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId,
                                   uint16_t pos_x, uint16_t pos_y) {


}

void GameClient::manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t hp) {

}

void GameClient::manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t vecx, uint16_t vecy) {

}

void GameClient::manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId) {

}

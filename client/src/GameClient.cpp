//
// Created by celeriy on 28/11/16.
//

#include <stdexcept>
#include <iostream>
#include <future>
#include "EventManager.hh"
#include "GameClient.hh"

using namespace client;

client::GameClient::GameClient()
{
  handler = new EventManager(this);
  manager = nullptr;
  tickRateClient = 0;
  world = nullptr;
  gameui = new GameUIInterface(handler);
  gameui->initUI();
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
  short	event;
  while (1)
    {
      gameui->displaySimple();
      event = handler->getEvent();
      if (event != -42)
	std::cout << event << std::endl;
    }
}

void	GameClient::readaptTickRate(int servTickRate,
				    std::pair<tick, uint64_t> estiClientHoro,
				    std::pair<tick, uint64_t> servHoro)
{
  double	tickRateModif;
  
  tickRateModif = (((double)(tickRateClient - servTickRate)) * TICKRATEDIFFCONST)
    * (((double)(estiClientHoro.first - servHoro.first)) * TICKCURRENTDIFFCONST)
    * (((double)(estiClientHoro.second - servHoro.second)) * HORODIFFCONST);
  if (tickRateModif < 0.0)
    --tickRateClient;
  else if (tickRateModif > 0.0)
    ++tickRateClient;
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

World *GameClient::getWorld() const
{
    return world;
}

void
GameClient::manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName,
			      uint16_t entityId, int16_t pos_x, int16_t pos_y, int16_t hp)
{
  typeide_t	type;

  type = gameui->registerNewSprite(spriteName);
  if (world != nullptr)
    world->spawnEntity(entityId, pos_t(pos_x, pos_y), type, eventId, tick);
}

void GameClient::manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp)
{
  if (world != nullptr)
    world->updateEntity(hp, tick, entityId, eventId);
}

void GameClient::manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId,
                                  int16_t vecx, int16_t vecy, int16_t posx, int16_t posy)
{
  if (world != nullptr)
    world->moveEntity(vec_t(vecx, vecy), pos_t(posx, posy), tick, entityId, eventId);
}

void GameClient::manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId)
{
  if (world != nullptr)
    world->deleteEntity(entityId, tick, eventId);
}

void GameClient::manageGameData(uint32_t turn, uint64_t time)
{
  if (world == nullptr)
    {
      world = new World();
      horodatageTick.insert(std::pair<tick, uint64_t>(static_cast<tick>(turn), time));
      tickRateClient = TICKRATE;
      //informer la gameUI
    }
  else
    horodatageTick.insert(std::pair<tick, uint64_t>(static_cast<tick>(turn), time));
}

void GameClient::manageDisconnect()
{
  manageQuit();
  deleteNetworkManager();
  // informer la gameUI
}

void GameClient::manageCancelEvent(uint32_t eventId)
{
}

void GameClient::manageGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList)
{
  gameui->feedGameList(gameList);
}

void GameClient::manageLeaderBoard(std::vector<std::pair<uint32_t, std::string> > LeaderBoard)
{
  gameui->feedLeaderBoard(LeaderBoard);
}

void GameClient::managePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName)
{
}

void GameClient::manageQuit() {
    if (world != nullptr) {
        delete world;
        horodatageTick.clear();
        tickRateClient = 0;
        world = nullptr;
    }
    //informer la gameUI
}
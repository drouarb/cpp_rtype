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
  handler = new EventManager;
  managerUi.init(1920, 1020);
  managerUi.getEventObserver()->setEventManager(handler);
  managerUi.getEventObserver()->listen(managerUi.getWindow(UI::MAIN_WINDOW));
  manager = nullptr;
  tickRateClient = TICKRATE;
  world = nullptr;
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

void	GameClient::gameLoop() {

    UI::IWindow *window = managerUi.getWindow(UI::MAIN_WINDOW);
    UI::IEventObserver *eventObserver = managerUi.getEventObserver();
    while (window->isOpen()) {
        window->display();
        eventObserver->getEvent();
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

World *GameClient::getWorld() const {
    return world;
}

void GameClient::manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName,
				   uint16_t entityId, uint16_t pos_x, uint16_t pos_y)
{
  typeide_t	type;

  type = gameui.registerNewSprite(spriteName);
  if (world != nullptr)
    world->spawnEntity(entityId, pos_t(pos_x, pos_y), type, eventId, tick);
}

void GameClient::manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t hp)
{
  if (world != nullptr)
    world->updateEntity(hp, tick, entityId, eventId);
}

void GameClient::manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId,
				  uint16_t vecx, uint16_t vecy, int16_t posx, int16_t posy)
{
  if (world != nullptr)
    world->moveEntity(vec_t(vecx, vecy), pos_t(posx, posy), tick, entityId, eventId);
}

void GameClient::manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId)
{
  if (world != nullptr)
    world->deleteEntity(entityId, tick, eventId);
}

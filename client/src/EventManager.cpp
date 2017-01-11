//
// Created by jonas_e on 12/2/16.
//

#include <EventManager.hh>

client::EventManager::EventManager(client::GameClient *ngameclient)
{
  gameClient = ngameclient;
}

client::EventManager::~EventManager()
{

}

void client::EventManager::onMouseRelease(short x, short y)
{

}

void client::EventManager::onKeyPressed(short key)
{
  std::cout << "--------------------PRESS" << key << std::endl;
  if (key != -42)
    if (events.size() == 0 || events[events.size() - 1].key != key
	|| events[events.size() - 1].pressed != true)
      events.push_back(client::Event(key, true));
}

void client::EventManager::onKeyRelease(short key)
{
  std::cout << "===========================RELEASE" << key << std::endl;
  if (key != -42)
    if (events.size() == 0 || events[events.size() - 1].key != key
	|| events[events.size() - 1].pressed != false)
      events.push_back(client::Event(key, false));
}

client::Event client::EventManager::getEvent()
{
  client::Event buff;

  if (events.size() > 0)
    {
      buff.key = events[0].key;
      buff.pressed = events[0].pressed;
      events.erase(events.begin());
    }
  else
    {
      buff.key = -42;
      buff.pressed = false;
    }
  return (buff);
}

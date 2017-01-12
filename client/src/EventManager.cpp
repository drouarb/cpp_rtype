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
  if (events.size() > 1)
    return;
  if (key != -42)
    if (events.size() == 0 || events[events.size() - 1].key != key
	|| events[events.size() - 1].pressed != true)
      events.push_back(client::Event(key, true));
}

void client::EventManager::onKeyRelease(short key)
{
  unsigned int i;
  i = 0;
  while (i < events.size())
    {
      if (events[i].key == key && events[i].pressed == false)
	return;
      ++i;
    }
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

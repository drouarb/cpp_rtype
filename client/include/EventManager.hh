//
// Created by jonas_e on 12/2/16.
//

#ifndef CPP_RTYPE_EVENTMANAGER_HH
#define CPP_RTYPE_EVENTMANAGER_HH

#include <SFML/Window/Keyboard.hpp>
#include "IEventHandler.hh"
#include "Definitions.hh"
#include "GameClient.hh"
#include <vector>

namespace client
{
  class EventManager : public IEventHandler
  {
  private:
    client::GameClient	*gameClient;
    std::vector<Event >	events;
  public:
    EventManager(client::GameClient *gameclient);
      
    ~EventManager();
      
    void onKeyPressed(short key);
      
    void onKeyRelease(short key);
      
    void onMouseRelease(short x, short y);
      
    client::Event getEvent();
      
  };
}


#endif //CPP_RTYPE_EVENTMANAGER_HH

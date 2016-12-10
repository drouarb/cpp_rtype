//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_GAMECLIENT_HH
#define CPP_RTYPE_GAMECLIENT_HH

#include <utility>
#include <mutex>
#include "World.hh"
#include "Entity.hh"
#include "NetworkManager.hh"
#include "Definitions.hh"

#define TICKRATE 60

namespace client
{
    class NetworkManager;
  
    class GameClient
    {
    private:
      std::mutex		client_mut;
      NetworkManager		*manager;
      tick			tickRateServer;
      std::map<tick, uint64_t>	horodatageTick;
    public:
      GameClient();
      ~GameClient(){};
      void createNetworkManager(const std::string &ip, unsigned short port);
      void deleteNetworkManager();
      void	gameLoop();
    private:
      void      readaptTickRate(int servTickRate,
				std::pair<tick, uint64_t> estiClientHoro,
				std::pair<tick, uint64_t> servHoro);
      int       calcTickRate(int nbrLevel);
    };
}

#endif //CPP_RTYPE_GAMECLIENT_HH

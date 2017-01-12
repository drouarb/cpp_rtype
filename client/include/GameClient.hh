//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_GAMECLIENT_HH
#define CPP_RTYPE_GAMECLIENT_HH

#include <utility>
#include "thread/Mutex.hh"
#include "World.hh"
#include "Entity.hh"
#include "NetworkManager.hh"
#include "GameUIInterface.hh"
#include "Definitions.hh"
#include "Information.hh"
#include "thread/Thread.hpp"
#include "helpers/IStopwatch.hh"

#define TICKRATE 35
#define TICKRATEDIFFCONST 0.1
#define TICKCURRENTDIFFCONST (1.0 / (((double)TICKRATE) * 5.0))
#define PERIODTICKEVENT 2

namespace client {

    class NetworkManager;

    class EventManager;

  class GameClient {
  private:
    World *world;
    EventManager *handler;
    Mutex *client_mut;
    NetworkManager *manager;
    int tickRateClient;
    std::map<tick, uint64_t> horodatageTick;
    GameUIInterface *gameui;
    ide_t playerId;
    uint8_t nbrAttack;
    helpers::IStopwatch *sw;
    std::map<client::Key, vec_t> keygame_move;
    std::map<client::Key, int> keygame_attack;
    std::list<std::string> name_key;
    IThread			*GameThread;
    bool			firstSynchro;
    vec_t			additioner;
    uint8_t			ttadd;
  public:

    static const std::map<client::Key, const std::string> keyStringMap;

    GameClient();

    ~GameClient() {};

    void createNetworkManager() {};

    void createNetworkManager(const std::string &ip, unsigned short port);

    void deleteNetworkManager();

    void gameLoop();

    void manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName,
			   uint32_t entityId, int16_t pos_x, int16_t pos_y, int16_t hp);

    void manageUpdateEntity(uint32_t tick, uint32_t eventId, uint32_t entityId, int16_t hp);

    void manageMoveEntity(uint32_t tick, uint32_t eventId, uint32_t entityId,
			  int16_t vecx, int16_t vecy, int16_t posx, int16_t posy);

    void manageDeleteEntity(uint32_t tick, uint32_t eventId, uint32_t entityId);

    void manageSyncro(uint32_t tick, int64_t time);

    void managePlayerData(uint32_t playerId, uint8_t nbAttackPlayer);

    void manageGameData();

    void manageDisconnect();

    void manageErrorGame(const std::string &Data);
    
    void sendAll(struct s_info *info);

    void sendMove();

    void manageCancelEvent(uint32_t eventId);

    void manageGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList);

    void manageLeaderBoard(std::vector<std::pair<uint32_t, std::string> > LeaderBoard);

    void managePlaySound(uint32_t tick, uint32_t eventId, const std::string &SoundName);

    void manageQuit();

    void run();

    World *getWorld() const;



    void  manageGameData(const std::string &audio, const std::string &background);
    void createKeyMap(const std::string &path);

    void saveConfig();


    bool touchExit(const std::string &data);

    int getTickRate() const;

    int getTouch(const std::string &data);
  private:
    void prepaStateMenus();

    void readaptTickRate(int servTickRate,
			 std::pair<tick, uint64_t> estiClientHoro,
			 std::pair<tick, uint64_t> servHoro);

    int calcTickRate(int nbrLevel);

  };
}
#endif //CPP_RTYPE_GAMECLIENT_HH

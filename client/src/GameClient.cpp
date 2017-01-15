//
// Created by celeriy on 28/11/16.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include "EventManager.hh"
#include "GameClient.hh"
#include <algorithm>

using namespace client;

client::GameClient::GameClient() {
  handler = new EventManager(this);
  manager = nullptr;
  tickRateClient = TICKRATE;
  world = nullptr;
  client_mut = new Mutex;
  sw = helpers::IStopwatch::getInstance();
  gameui = new GameUIInterface(handler);
  gameui->initUI();
  createKeyMap("config/gameCommand.json");
  additioner.first = 0;
  additioner.second = 0;
  ttadd = 0;
}

void client::GameClient::createNetworkManager(const std::string &ip, unsigned short port) {
  try {
    deleteNetworkManager();
    manager = new NetworkManager(ip, port, this);
    manager->addListenerToPacketFactory();
    manager->startPacketFactory();
  }
  catch (std::runtime_error *e) {
    gameui->showError("Cannot join the server");
    manager = nullptr;
  }
}

void client::GameClient::deleteNetworkManager() {
  delete (manager);
  manager = nullptr;
}

void GameClient::readaptTickRate(int servTickRate,
                                 std::pair<tick, uint64_t> estiClientHoro,
                                 std::pair<tick, uint64_t> servHoro) {
  double tickRateModif;

  tickRateModif = (((double) ((tickRateClient) - servTickRate)) * TICKRATEDIFFCONST)
    + (((double) (((int64_t) estiClientHoro.first) - (int64_t) servHoro.first)) * TICKCURRENTDIFFCONST);
  if (tickRateModif < 0.0)
    ++tickRateClient;
  else if (tickRateClient > 1 && tickRateModif > 0.0)
    --tickRateClient;
}

int GameClient::calcTickRate(int nbrLevel) {
  std::map<tick, uint64_t>::iterator it;
  tick tickBegin;
  uint64_t timeBegin;
  tick tickEnd;
  uint64_t timeEnd;

  if (nbrLevel > horodatageTick.size())
    return (TICKRATE);
  it = horodatageTick.end();
  --it;
  tickBegin = it->first;
  timeBegin = it->second;
  while (nbrLevel > 0 && it != horodatageTick.begin()) {
    --it;
    --nbrLevel;
  }
  if (horodatageTick.begin() == it)
    return (TICKRATE);
  tickEnd = it->first;
  timeEnd = it->second;
  return (((tickBegin - tickEnd) * 1000) / (((timeBegin - timeEnd) + 0.0000001)));
}

World *GameClient::getWorld() const {
  return world;
}

void
GameClient::manageSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName,
                              uint32_t entityId, int32_t pos_x, int32_t pos_y, int16_t hp) {
  typeide_t type;

  type = gameui->registerNewSprite(spriteName);
  if (world != nullptr) {
    world->spawnEntity(entityId, pos_t(pos_x, pos_y), type, eventId, tick);
  }
}

void GameClient::manageUpdateEntity(uint32_t tick, uint32_t eventId, uint32_t entityId, int16_t hp) {
  if (world != nullptr)
    world->updateEntity(hp, tick, entityId, eventId);
}

void GameClient::manageMoveEntity(uint32_t tick, uint32_t eventId, uint32_t entityId,
                                  int32_t vecx, int32_t vecy, int32_t posx, int32_t posy) {
  if (world != nullptr)
    {
      //if (entityId == playerId)
      //std::cout << "ici player move " << vecx << " tick : " << tick << std::endl;
      world->moveEntity(vec_t(vecx, vecy), pos_t(posx, posy), tick, entityId, eventId);
    }
}

void GameClient::manageDeleteEntity(uint32_t tick, uint32_t eventId, uint32_t entityId) {
  if (world != nullptr) {
    world->deleteEntity(entityId, tick, eventId);
  }
}

void GameClient::managePlayerData(uint32_t nplayerId, uint8_t nbAttackPlayer) {
  if (world == nullptr) {
    horodatageTick.clear();
    firstSynchro = false;
    world = new World(gameui);
    playerId = nplayerId;
    nbrAttack = nbAttackPlayer;
    tickRateClient = TICKRATE;
  } else {
    playerId = nplayerId;
    nbrAttack = nbAttackPlayer;
  }


}

void GameClient::manageSyncro(uint32_t turn, int64_t time) {
  std::map<tick, uint64_t>::iterator it;
  
  it = horodatageTick.end();
  if (firstSynchro == false)
    {
      firstSynchro = true;
      world->setTick(turn);
    }
  if (horodatageTick.size() == 0)
    {
      horodatageTick.insert(std::pair<tick, uint64_t>(static_cast<tick>(turn), time));
      return;
    }
  else
    {
      --it;
      if (it->second < time)
	horodatageTick.insert(std::pair<tick, uint64_t>(static_cast<tick>(turn), time));
    }
}

void GameClient::manageGameData() {
}

void GameClient::manageDisconnect() {
  std::cout << "Receive Disconnect" << std::endl;
  gameui->showError("Disconnect from the server");
  manageQuit();
  gameui->changeMenu("MenuSplash");
}

void GameClient::manageCancelEvent(uint32_t eventId) {

}

void GameClient::manageGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList) {
  gameui->feedGameList(gameList);
  gameui->reloadMenuRoomList();
}

void GameClient::manageLeaderBoard(std::vector<std::pair<uint32_t, std::string> > LeaderBoard) {
  gameui->feedLeaderBoard(LeaderBoard);
  gameui->reloadMenuRoomList();
}

void GameClient::managePlaySound(uint32_t tick, uint32_t eventId, const std::string &SoundName) {
  gameui->addSound(SoundName);
  gameui->playSoundEffect(SoundName);
}

void GameClient::manageQuit() {
  if (world != nullptr) {
    delete world;
    world = nullptr;
    horodatageTick.clear();
    tickRateClient = 0;
    firstSynchro = false;
    sendAll(client::parse(I_LEADERBOARD, client::Key::KEY_ESCAPE));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    horodatageTick.clear();
  }
}

void GameClient::run() {
  GameThread = new Thread<decltype(&GameClient::gameLoop), GameClient *>(&GameClient::gameLoop, this);
  gameui->UILoop();
}

void GameClient::gameLoop() {
  Event event;
  std::vector<std::pair<UIevent_t, pos_t> > WorldEvent;
  std::vector<s_info *> receive;
  tick tickcpt;
  unsigned int i;

  while (gameui->windowIsOpen()) {
    tickcpt = 0;
    while (tickcpt < tickRateClient) {
      sw->set();
      if (tickcpt % PERIODTICKEVENT == 0) {
	event = handler->getEvent();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	receive.clear();
	receive = gameui->manageInput(event);
	i = 0;
	while (i < receive.size())
	  {
	    if (receive[i] != nullptr)
	      {
		if (receive[i]->info == I_QUIT)
		  {
		    deleteNetworkManager();
		    gameui->stopUI();
		    return;
		  }
		sendAll(receive[i]);
		delete (receive[i]);
	      }
	    ++i;
	  }
	sendMove();
      }
      if (world != nullptr)
	world->applyTurn(tickRateClient, playerId);
      ++tickcpt;
      if (tickRateClient != 0 && sw->elapsedMs() < 1000 / (tickRateClient))
	std::this_thread::sleep_for(std::chrono::milliseconds((1000 / tickRateClient) - sw->elapsedMs()));
    }
    if (world != nullptr && horodatageTick.size() > 1) {
      std::map<tick, uint64_t>::iterator it;
      it = horodatageTick.end();
      --it;
      readaptTickRate(calcTickRate(3), std::pair<tick, uint64_t>(world->getTick(), std::time(nullptr)),
		      std::pair<tick, uint64_t>(it->first, it->second));
    } else
      tickRateClient = TICKRATE;
  }
  gameui->stopUI();
}

void GameClient::sendAll(struct s_info *info) {
  switch (info->info) {
  case I_CONNECTION: {
    createNetworkManager(static_cast<s_connection *>(info)->ip, static_cast<s_connection *>(info)->port);
    if (manager != nullptr)
      gameui->changeMenu("MenuRegister");
  }
    break;
  case I_REGISTER: {
    if (manager != nullptr) {
      manager->sendRegister(static_cast<s_register *>(info)->name);
      manager->sendAskList();
      gameui->changeMenu("roomList");
    }
  }
    break;
  case I_ASK: {
    if (manager != nullptr) {
      manager->sendAskList();
    }
  }
    break;
  case I_ASKLIST: {
    if (manager != nullptr) {
      manager->sendQuit();
      manager->sendAskList();
      gameui->playSound("media/musics/moh.ogg");
      gameui->changeMenu("roomList");
      if (world != nullptr) {
	delete world;
	world = nullptr;
	horodatageTick.clear();
	tickRateClient = 0;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	horodatageTick.clear();
      }
    }
  }
    break;
  case I_CREDIT:
    gameui->credit();
    break;
  case I_JOIN: {
    if (manager != nullptr) {
      manager->sendJoin(static_cast<s_join *>(info)->roomid);
      gameui->changeMenu("game");
    }
  }
    break;
  case I_SAVE: {
    saveConfig();
  }
    break;
  case I_LEADERBOARD: {
    if (manager != nullptr) {
      gameui->changeMenu("LeaderBoard");
    }
  }
    break;
  case I_ASKLEADERBOARD: {
    if (manager != nullptr) {
      manager->sendAskLearderBoard();
      gameui->changeMenu("LeaderBoard");
    }
  }
    break;
  case I_PLAYER :
    {
      if (manager != nullptr && world != nullptr && world->getEntityById(playerId) != nullptr)
	{
	  if (keygame_move.find(static_cast<s_player *>(info)->key) != keygame_move.end())
	    {
	      /*world->getEntityById(playerId)->moveEntity(keygame_move[static_cast<s_player *>(info)->key],
		pos_t(world->getEntityById(playerId)->getPos().first,
		world->getEntityById(playerId)->getPos().second),
		world->getTick());
		manager->sendPlayerMove(world->getTick(), world->getEntityById(playerId)->getVec().first,
		world->getEntityById(playerId)->getVec().second,
		world->getEntityById(playerId)->getPos().first,
		world->getEntityById(playerId)->getPos().second);*/
	      additioner.first += keygame_move[static_cast<s_player *>(info)->key].first;
	      additioner.second += keygame_move[static_cast<s_player *>(info)->key].second;
	    }
	  if (keygame_attack.find(static_cast<s_player *>(info)->key) != keygame_attack.end())
	    {
	      manager->sendPlayerAttack(world->getTick(), keygame_attack[static_cast<s_player *>(info)->key]);
	    }
	  ++ttadd;
	}
    }
    break;
  default:
    {
      std::cout << "nop" << std::endl;
    break;
    }
  }
}

void GameClient::sendMove()
{
  if (ttadd > 0)
    {
      additioner.first /= ttadd;
      additioner.second /= ttadd;
      world->getEntityById(playerId)->moveEntity(additioner,
						 pos_t(world->getEntityById(playerId)->getPos().first,
						       world->getEntityById(playerId)->getPos().second),
						 world->getTick());
      manager->sendPlayerMove(world->getTick(), additioner.first / 100, additioner.second / 100,
			      world->getEntityById(playerId)->getPos().first,
			      world->getEntityById(playerId)->getPos().second);
    }
  additioner.first = 0;
  additioner.second = 0;
  ttadd = 0;
}

void GameClient::createKeyMap(const std::string &path) {

  boost::property_tree::ptree root;
  read_json(path, root);
  keygame_move.clear();
  keygame_attack.clear();
  name_key.clear();
  BOOST_FOREACH(boost::property_tree::ptree::value_type
		child, root.get_child("Move")) {
    keygame_move[static_cast<client::Key >(child.second.get<int>(
								 "value"))] = std::pair<int16_t, int16_t>(
													  child.second.get<int>("x"),
													  child.second.get<int>("y"));
  
    gameui->setStringToButtons("key" + child.second.get<std::string>("name"), keyStringMap.at(static_cast<client::Key>(child.second.get<int>("value"))), "MenuOption");
    name_key.push_back(child.second.get<std::string>("name"));
  }

  BOOST_FOREACH(boost::property_tree::ptree::value_type
		child, root.get_child("Attack")) {
    keygame_attack[static_cast<client::Key >(child.second.get<int>("value"))] = child.second.get<int>(
												      "id");
    gameui->setStringToButtons("key" + child.second.get<std::string>("name"), keyStringMap.at(
											      static_cast<client::Key>(child.second.get<int>(
																	     "value"))), "MenuOption");
    name_key.push_back(child.second.get<std::string>("name"));
  }

  BOOST_FOREACH(boost::property_tree::ptree::value_type
		child, root.get_child("gameList")) {
    gameui->setKeygameList(static_cast<client::Key>(child.second.get<int>("value")));
    gameui->setStringToButtons("key" + child.second.get<std::string>("name"), keyStringMap.at(
											      static_cast<client::Key>(child.second.get<int>(
																	     "value"))), "MenuOption");
    name_key.push_back(child.second.get<std::string>("name"));
  }

  BOOST_FOREACH(boost::property_tree::ptree::value_type
		child, root.get_child("leaderBoard")) {
    gameui->setKeyLeaderBoard(static_cast<client::Key>(child.second.get<int>("value")));
    gameui->setStringToButtons("key" + child.second.get<std::string>("name"), keyStringMap.at(
											      static_cast<client::Key>(child.second.get<int>(
																	     "value"))), "MenuOption");
    name_key.push_back(child.second.get<std::string>("name"));
  }
}

void GameClient::saveConfig() {
  boost::property_tree::ptree root;
  read_json("config/gameCommand.json", root);
  std::string key;
  for (auto it = name_key.begin(); it != name_key.end(); it++) {
    if (touchExit(gameui->getStringFromButtons("key" + *it, "MenuOption")) == true) {
      key = (gameui->getStringFromButtons("key" + *it, "MenuOption"));
      BOOST_FOREACH(boost::property_tree::ptree::value_type
		    &child, root.get_child("Move")) {
	if (child.second.get<std::string>("name") == (*it))
	  child.second.put<int>("value", getTouch(key));
      }
      BOOST_FOREACH(boost::property_tree::ptree::value_type
		    &child, root.get_child("Attack")) {
	if (child.second.get<std::string>("name") == (*it))
	  child.second.put<int>("value", getTouch(key));
      }
      BOOST_FOREACH(boost::property_tree::ptree::value_type
		    &child, root.get_child("leaderBoard")) {
	if (child.second.get<std::string>("name") == (*it))
	  child.second.put<int>("value", getTouch(key));
      }
      BOOST_FOREACH(boost::property_tree::ptree::value_type
		    &child, root.get_child("gameList")) {
	if (child.second.get<std::string>("name") == (*it)) {
	  child.second.put<int>("value", getTouch(key));

	}
      }

    }
  }
  write_json("config/gameCommand.json", root);
  createKeyMap("config/gameCommand.json");
}

bool GameClient::touchExit(const std::string &data) {
  for (auto it = keyStringMap.begin(); it != keyStringMap.end(); it++) {
    if (it->second == data)
      return true;
  }
  return false;
}

int GameClient::getTickRate() const {
  return (tickRateClient);
}

int GameClient::getTouch(const std::string &data) {
  for (auto it = keyStringMap.begin(); it != keyStringMap.end(); it++) {
    if (it->second == data)
      return static_cast<int>(it->first);
  }
  return 1000;
}

void GameClient::manageGameData(const std::string &audio, const std::string &background) {
  gameui->playSound("media/" + audio);
  gameui->addBackground("media/" + background);

}

void GameClient::manageErrorGame(const std::string &Data) {

  gameui->showError(Data);
  sendAll(parse(I_ASKLIST, client::KEY_ESCAPE));
}

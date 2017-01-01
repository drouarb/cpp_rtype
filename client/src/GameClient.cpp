//
// Created by celeriy on 28/11/16.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <stdexcept>
#include <iostream>
#include <future>
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
    std::cout << "Server. current tick : [" << servHoro.first << "] tickrate : " << servTickRate << std::endl;
    std::cout << "Client. current tick : [" << estiClientHoro.first << "] tickrate : " << tickRateClient << std::endl;
    std::cout << "Client tickrate " << ((tickRateModif < 0.0) ? "increase of + 1" : "decrease of - 1") << std::endl;
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
                              uint16_t entityId, int16_t pos_x, int16_t pos_y, int16_t hp) {
    typeide_t type;

    type = gameui->registerNewSprite(spriteName);
    if (world != nullptr) {
        world->spawnEntity(entityId, pos_t(pos_x, pos_y), type, eventId, tick);
    }
}

void GameClient::manageUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp) {
    if (world != nullptr)
        world->updateEntity(hp, tick, entityId, eventId);
}

void GameClient::manageMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId,
                                  int16_t vecx, int16_t vecy, int16_t posx, int16_t posy) {
    if (world != nullptr)
      {
	//if (entityId == playerId)
	  //std::cout << "ici player move " << vecx << " tick : " << tick << std::endl;
        world->moveEntity(vec_t(vecx, vecy), pos_t(posx, posy), tick, entityId, eventId);
      }
}

void GameClient::manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId) {
    if (world != nullptr) {
        world->deleteEntity(entityId, tick, eventId);
    }
}

void GameClient::managePlayerData(uint16_t nplayerId, uint8_t nbAttackPlayer) {
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
    horodatageTick.insert(std::pair<tick, uint64_t>(static_cast<tick>(turn), time));
    if (firstSynchro == false)
      {
	firstSynchro = true;
	world->setTick(turn);
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
    std::cerr << "je passe" << std::endl;
}

void GameClient::managePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName) {
}

void GameClient::manageQuit() {
    if (world != nullptr) {
        delete world;
        horodatageTick.clear();
        tickRateClient = 0;
        world = nullptr;
	firstSynchro = false;
        sendAll(client::parse(I_LEADERBOARD, client::Key::KEY_ESCAPE));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        horodatageTick.clear();
    }
}

void GameClient::run() {
  	GameThread = new Thread<decltype(&GameClient::gameLoop), GameClient *>(&GameClient::gameLoop, this);
    	gameui->UILoop();
	//gameLoop();
}

void GameClient::gameLoop() {
    short event;
    std::vector<std::pair<UIevent_t, pos_t> > WorldEvent;
    s_info *receive = nullptr;
    tick tickcpt;

    while (gameui->windowIsOpen()) {
      tickcpt = 0;
      while (tickcpt < tickRateClient) {
	sw->set();
	if (tickcpt % PERIODTICKEVENT == 0) {
	  event = handler->getEvent();
	  if (event != -42) {
	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
	    receive = gameui->manageInput(event);
	    if (receive != nullptr) {
	      if (receive->info == I_QUIT) {
		deleteNetworkManager();
		gameui->stopUI();
		return;
	      }
	      sendAll(receive);
	      delete (receive);
	    }
	    event = -42;
	  } else if (world != nullptr && playerId != -1 && world->getEntityById(playerId) != nullptr) {
	    world->getEntityById(playerId)->moveEntity(vec_t(0, 0), pos_t(world->getEntityById(playerId)->getPos().first, world->getEntityById(playerId)->getPos().second), world->getTick());
	    manager->sendPlayerMove(world->getTick(), world->getEntityById(playerId)->getVec().first,
				    world->getEntityById(playerId)->getVec().second,
				    world->getEntityById(playerId)->getPos().first,
				    world->getEntityById(playerId)->getPos().second);
	  }
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
                    horodatageTick.clear();
                    tickRateClient = 0;
                    world = nullptr;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    horodatageTick.clear();
                }
            }
        }
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
        case I_PLAYER : {
            if (manager != nullptr && world != nullptr && world->getEntityById(playerId) != nullptr) {
                if (keygame_move.find(static_cast<s_player *>(info)->key) != keygame_move.end()) {
                    world->getEntityById(playerId)->moveEntity(keygame_move[static_cast<s_player *>(info)->key],
                                                               pos_t(world->getEntityById(playerId)->getPos().first,
                                                                     world->getEntityById(playerId)->getPos().second),
                                                               world->getTick());
                    manager->sendPlayerMove(world->getTick(), world->getEntityById(playerId)->getVec().first,
                                            world->getEntityById(playerId)->getVec().second,
                                            world->getEntityById(playerId)->getPos().first,
                                            world->getEntityById(playerId)->getPos().second);
                }
                if (keygame_attack.find(static_cast<s_player *>(info)->key) != keygame_attack.end()) {
                    manager->sendPlayerAttack(world->getTick(), keygame_attack[static_cast<s_player *>(info)->key]);
                }
            }
        }
            break;
        default:
            break;
    }
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
                    gameui->setStringToButtons("key" + child.second.get<std::string>("name"), keyStringMap.at(
                            static_cast<client::Key>(child.second.get<int>(
                                    "value"))), "MenuOption");
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

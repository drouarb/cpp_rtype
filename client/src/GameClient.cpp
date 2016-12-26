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

using namespace boost::property_tree;
using namespace client;

client::GameClient::GameClient() {
    handler = new EventManager(this);
    manager = nullptr;
    tickRateClient = TICKRATE;
    world = nullptr;
    client_mut = new std::mutex;
    sw = helpers::IStopwatch::getInstance();
    gameui = new GameUIInterface(handler, client_mut);
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
    catch (std::runtime_error &e) {
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

    tickRateModif = (((double) (tickRateClient - servTickRate)) * TICKRATEDIFFCONST)
                    * (((double) (estiClientHoro.first - servHoro.first)) * TICKCURRENTDIFFCONST)
                    * (((double) (estiClientHoro.second - servHoro.second)) * HORODIFFCONST);
    if (tickRateModif < 0.0)
        --tickRateClient;
    else if (tickRateModif > 0.0)
        ++tickRateClient;
}

int GameClient::calcTickRate(int nbrLevel) {
    std::map<tick, uint64_t>::iterator it;
    tick tickBegin;
    uint64_t timeBegin;
    tick tickEnd;
    uint64_t timeEnd;

    it = horodatageTick.end();
    --it;
    tickBegin = it->first;
    timeBegin = it->second;
    while (nbrLevel > 0 && it != horodatageTick.begin()) {
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
        world->moveEntity(vec_t(vecx, vecy), pos_t(posx, posy), tick, entityId, eventId);
}

void GameClient::manageDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId) {
    if (world != nullptr) {
        world->deleteEntity(entityId, tick, eventId);
    }
}

void GameClient::managePlayerData(uint16_t nplayerId, uint8_t nbAttackPlayer) {
    if (world == nullptr) {
        playerId = nplayerId;
        nbrAttack = nbAttackPlayer;
        world = new World(client_mut, gameui);
        tickRateClient = TICKRATE;
    }
}

void GameClient::manageSyncro(uint32_t turn, int64_t time) {
    horodatageTick.insert(std::pair<tick, uint64_t>(static_cast<tick>(turn), time));
}

void GameClient::manageGameData() {
}

void GameClient::manageDisconnect() {
    std::cout << "Receive Disconnect" << std::endl;
    manageQuit();
    deleteNetworkManager();
    // informer la gameUI
    exit(0); // supr
}

void GameClient::manageCancelEvent(uint32_t eventId) {
}

void GameClient::manageGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList) {
    gameui->feedGameList(gameList);
    gameui->reloadMenuRoomList();
}

void GameClient::manageLeaderBoard(std::vector<std::pair<uint32_t, std::string> > LeaderBoard) {
    gameui->feedLeaderBoard(LeaderBoard);
}

void GameClient::managePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName) {
}

void GameClient::manageQuit() {
    if (world != nullptr) {
        std::cout << "Receive Disconnect" << std::endl;
        delete world;
        horodatageTick.clear();
        tickRateClient = 0;
        world = nullptr;
    }
}

void GameClient::gameLoop() {
    short event;
    std::vector<std::pair<UIevent_t, pos_t> > WorldEvent;
    s_info *receive = nullptr;
    while (gameui->windowIsOpen()) {
        sw->set();
        gameui->updateListEntity();
        event = handler->getEvent();
        gameui->displaySimple();
        if (world != nullptr)
            world->applyTurn();
        if (event != -42) {
            receive = gameui->manageInput(event);
            if (receive != nullptr) {
                if (receive->info == I_QUIT)
                    break;
                sendAll(receive);
                delete (receive);
            }
        }
    }
    deleteNetworkManager();

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
        case I_ASKLIST: {
            if (manager != nullptr) {
                 manager->sendAskList();
                gameui->changeMenu("roomList");
                manager->sendQuit();
            }
        }
            break;
        case I_JOIN: {
            if (manager != nullptr) {
                manager->sendJoin(static_cast<s_join *>(info)->roomid);
                std::cout << "room id " << static_cast<s_join *>(info)->roomid << std::endl;
                gameui->changeMenu("game");
            }
        }
            break;
        case I_PLAYER : {
            if (manager != nullptr && world != nullptr) {
                if (keygame_move.find(static_cast<s_player *>(info)->key) != keygame_move.end()) {
                    world->getEntityById(playerId)->setVec(keygame_move[static_cast<s_player *>(info)->key]);
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

    ptree root;
    read_json(path, root);
    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("Move")) {
                    keygame_move[static_cast<client::Key >(child.second.get<int>("value"))] = std::pair<int16_t, int16_t>(
                            child.second.get<int>("x"),
                            child.second.get<int>("y"));
                }

    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("Attack")) {
                    keygame_attack[static_cast<client::Key >(child.second.get<int>("value"))] = child.second.get<int>("id");
                }
}

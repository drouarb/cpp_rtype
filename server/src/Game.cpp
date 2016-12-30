#include <algorithm>
#include <iostream>
#include <entities/Player.hh>
#include <events/Spawn.hh>
#include <events/Move.hh>
#include <events/ModHP.hh>
#include <events/Destroy.hh>
#include <network/packet/PacketSpawnEntity.hh>
#include <network/packet/PacketMoveEntity.hh>
#include <network/packet/PacketSynchronization.hh>
#include <ctime>
#include <network/packet/PacketPlayerData.hh>
#include <network/packet/PacketPlaySound.hh>
#include <network/packet/PacketLeaderBoard.hh>
#include <network/packet/PacketErrorGame.hh>
#include "Game.hh"

using namespace server;

Game::Game(network::PacketFactory & packetf, int lobbyId) : packetf(packetf), lvl(nullptr), round(0), gameId(lobbyId), entityIdCount(0), lastSyn(0), going(true)
{ }

Game::Game(network::PacketFactory & packetf, int lobbyId, const Level & lvl) : packetf(packetf), lvl(&lvl), round(0), gameId(lobbyId), entityIdCount(0), lastSyn(0), going(true)
{ }

Game::~Game()
{
    for (auto client : clientList)
    {
        removePlayer(client);
    }
    for (auto entity : entities)
    {
        delete entity;
    }
    for (auto entity : destroyedEntities)
    {
        delete entity;
    }
}

bool Game::operator==(const Game &other)
{
    return (this == &other);
}

void Game::setLevel(const Level & lvl)
{
    this->lvl = &lvl;
}

void Game::tick()
{
    round++;
    progressLevel();
    checkCollisions(); //must be before moveEntities
    moveEntities();
    letEntitesAct(); //must be called after checkCollisions
    unspawn(); //must be after letEntitiesAct
    this->sendData();
}

gameId_t Game::getLobbyId()
{
    return (gameId);
}

void Game::progressLevel()
{
    if (lvl)
    {
        const std::vector<Spawn> *pVector = lvl->getNewSpawns(round);
        if (pVector == NULL)
        {
            return;
        }
        for (auto spawn : *pVector)
        {
            Entity * entity = spawn.trigger(entityIdCount, round, entities);
            if (entity == nullptr)
            {
                LOG_ERROR("Game " << gameId << ": failed to create player " << spawn.dlName << std::endl);
            }
            else
            {
                INFO("Game " << gameId << ": Adding new player(" << spawn.dlName << " on: " << entity->data.getPosX() << ", " << entity->data.getPosY());
                entityIdCount++;
                entities.push_back(entity);
                this->sim_spawn(entity);
            }
        }
    }
}

void Game::checkCollisions()
{
    collisions = std::vector<CollisionWall>(entities.size());

    size_t max = entities.size();
    for (size_t i = 0; i < max; ++i)
    {
        for (size_t j = i + 1; j < max; ++j)
        {
            checkCollision(i, j);
        }
    }
}

void Game::checkCollision(int i, int j)
{
    //TODO: lighten code

    if (entities[i]->obj->collidesWith(*entities[j]) == T_FALSE && entities[j]->obj->collidesWith(*entities[i]) == T_FALSE)
        return;
    if (entities[i]->obj->collidesWith(*entities[j]) == NA || entities[j]->obj->collidesWith(*entities[i]) == NA)
        return;

    int dist;

    // calculations are based on entity[i]

    // --- x axis

    // - left edge
    if (entities[j]->data.getPosX() < entities[i]->data.getPosX() &&
        ((fy(i) >= fy(j) && fy(i) <= fyp(j)) || (fyp(i) >= fy(j) && fyp(i) <= fyp(j))))
    {
        dist = fx(i) - fxp(j);
        std::cout << "left dist=" << std::to_string(dist) << std::endl;
        if (dist <= 0)
        {
            entities[i]->obj->collide(*entities[j], this->round);
            entities[j]->obj->collide(*entities[i], this->round);

            if (entities[i]->data.getVectX() <= 0)
            {
                if (dist >= entities[i]->data.getVectX())
                {
                    entities[i]->data.setVectX(entities[i]->data.getVectX() - dist);
                    this->sim_move(entities[i]);
                    dist = 0;
                }
                else
                {
                    dist -= entities[i]->data.getVectX();
                    entities[i]->data.setVectX(0);
                    this->sim_move(entities[i]);
                }
            }
            if (entities[j]->data.getVectX() >= 0)
            {
                if (-dist <= entities[j]->data.getVectX())
                {
                    entities[j]->data.setVectX(entities[j]->data.getVectX() - -dist);
                    this->sim_move(entities[i]);
                }
                else
                {
                    entities[j]->data.setVectX(0);
                    this->sim_move(entities[i]);
                }
            }

            collisions[i].add(X, NEG);
            collisions[j].add(X, POS);
        }
    }

    // - right edge
    else if (entities[j]->data.getPosX() > entities[i]->data.getPosX() &&
        ((fy(i) >= fy(j) && fy(i) <= fyp(j)) || (fyp(i) >= fy(j) && fyp(i) <= fyp(j))))
    {
        dist = fx(j) - fxp(i);
        std::cout << "right dist=" << std::to_string(dist) << std::endl;
        if (dist <= 0)
        {
            entities[i]->obj->collide(*entities[j], this->round);
            entities[j]->obj->collide(*entities[i], this->round);

            if (entities[j]->data.getVectX() <= 0)
            {
                if (dist >= entities[j]->data.getVectX())
                {
                    entities[j]->data.setVectX(entities[j]->data.getVectX() - dist);
                    this->sim_move(entities[i]);
                    dist = 0;
                }
                else
                {
                    dist -= entities[j]->data.getVectX();
                    entities[j]->data.setVectX(0);
                    this->sim_move(entities[i]);
                }
            }
            if (entities[i]->data.getVectX() >= 0)
            {
                if (-dist <= entities[i]->data.getVectX())
                {
                    entities[i]->data.setVectX(entities[i]->data.getVectX() - -dist);
                    this->sim_move(entities[i]);
                }
                else
                {
                    entities[i]->data.setVectX(0);
                    this->sim_move(entities[i]);
                }
            }

            collisions[i].add(X, POS);
            collisions[j].add(X, NEG);
        }
    }

    // --- y axis

    // - upper edge
    if (entities[j]->data.getPosY() < entities[i]->data.getPosY() &&
        ((fx(i) >= fx(j) && fx(i) <= fxp(j)) || (fxp(i) >= fx(j) && fxp(i) <= fxp(j))))
    {
        dist = fy(i) - fyp(j);
        std::cout << "up dist=" << std::to_string(dist) << std::endl;
        if (dist <= 0)
        {
            entities[i]->obj->collide(*entities[j], this->round);
            entities[j]->obj->collide(*entities[i], this->round);

            if (entities[i]->data.getVectY() <= 0)
            {
                if (dist >= entities[i]->data.getVectY())
                {
                    entities[i]->data.setVectY(entities[i]->data.getVectY() - dist);
                    this->sim_move(entities[i]);
                    dist = 0;
                }
                else
                {
                    dist -= entities[i]->data.getVectY();
                    entities[i]->data.setVectY(0);
                    this->sim_move(entities[i]);
                }
            }
            if (entities[j]->data.getVectY() >= 0)
            {
                if (-dist <= entities[j]->data.getVectY())
                {
                    entities[j]->data.setVectY(entities[j]->data.getVectY() - -dist);
                    this->sim_move(entities[i]);
                }
                else
                {
                    entities[j]->data.setVectY(0);
                    this->sim_move(entities[i]);
                }
            }

            collisions[i].add(Y, NEG);
            collisions[j].add(Y, POS);
        }
    }

    // - lower edge
    else if (entities[j]->data.getPosY() > entities[i]->data.getPosY() &&
        ((fx(i) >= fx(j) && fx(i) <= fxp(j)) || (fxp(i) >= fx(j) && fxp(i) <= fxp(j))))
    {
        dist = fy(j) - fyp(i);
        std::cout << "down dist=" << std::to_string(dist) << std::endl;
        if (dist <= 0)
        {
            entities[i]->obj->collide(*entities[j], this->round);
            entities[j]->obj->collide(*entities[i], this->round);

            if (entities[j]->data.getVectY() <= 0)
            {
                if (dist >= entities[j]->data.getVectY())
                {
                    entities[j]->data.setVectY(entities[j]->data.getVectY() - dist);
                    this->sim_move(entities[i]);
                    dist = 0;
                }
                else
                {
                    dist -= entities[j]->data.getVectY();
                    entities[j]->data.setVectY(0);
                    this->sim_move(entities[i]);
                }
            }
            if (entities[i]->data.getVectY() >= 0)
            {
                if (-dist <= entities[i]->data.getVectY())
                {
                    entities[i]->data.setVectY(entities[i]->data.getVectY() - -dist);
                    this->sim_move(entities[i]);
                }
                else
                {
                    entities[i]->data.setVectY(0);
                    this->sim_move(entities[i]);
                }
            }

            collisions[i].add(Y, POS);
            collisions[j].add(Y, NEG);
        }
    }
}

void Game::letEntitesAct()
{
    for (size_t i = 0; i != entities.size(); ++i)
    {
        auto it = entities.at(i);
        EntityAction * action = it->obj->act(this->round, entities);
        collisions[i].apply(action);
        if (action->speedX != it->data.getVectX())
        {
            it->data.setVectX(action->speedX);
            this->sim_move(entities[i]);
        }
        if (action->speedY != it->data.getVectY())
        {
            it->data.setVectY(action->speedY);
            this->sim_move(entities[i]);
        }
        if (action->hp != it->data.getHp())
        {
            it->data.setHp(action->hp);
            this->sim_update(entities[i]);
        }
        if (action->newEntity)
        {
            entities.push_back(new Entity(action->newEntity, entityIdCount, round, entities));
            entityIdCount++;
            this->sim_spawn(entities.back());
        }
        if (action->destroy)
        {
            it->data.setDestroyed(true);
        }
        if (action->soundToPlay != "")
        {
            sendSound(action->soundToPlay);
        }
        delete action;
    }
}

void Game::moveEntities()
{
    for (auto entity : entities)
    {
        entity->data.setPosX(entity->data.getPosX() + entity->data.getVectX());
        entity->data.setPosY(entity->data.getPosY() + entity->data.getVectY());
    }
}

void Game::unspawn()
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        if ((*it)->data.getPosX() <= FIELD_BORDER_LEFT - LEFT_MARGIN || (*it)->data.getPosX() > FIELD_BORDER_RIGHT + RIGHT_MARGIN
                || (*it)->data.getPosY() + (*it)->data.getSprite().sizeY < 0 || (*it)->data.getPosY() > FIELD_HEIGHT)
        {
            (*it)->data.setDestroyed(true);
            INFO("OUT OF RANGE : " << (*it)->data.getId())
        }
        if ((*it)->data.isDestroyed())
        {
            INFO("delete player : " << (*it)->data.getId())
            this->sim_destroy(*it);
            destroyedEntities.push_back(*it);
            it = vect_erase(it, entities);

            if (going && isFinished())
                endGame();
        }
        else
            ++it;
    }

}

void Game::newPlayer(Client *client) {
    INFO("Adding player from " << client->getClientId())

    if (clientList.size() == 4)
    {
        INFO("Full")
        network::packet::PacketErrorGame packet;
        packet.setMessage("Game room number " + std::to_string(gameId) + " is full.");
        packetf.send(packet, client->getClientId());
        return;
    }

    Controller *controller = new Controller();
    this->clientList.push_back(client);
    Player *player = new Player();
    Entity *entity = new Entity();
    controller->setEntity(entity);
    entity->initialize(player, entityIdCount, round, entities);
    entityIdCount++;
    controller->setEntity(player);
    client->setController(controller);
    this->entities.push_back(entity);
    this->sim_spawn(entity);
    greetNewPlayer(*client);
}

void Game::removePlayer(Client *client) {
    const std::list<server::Client *>::iterator &position = std::find(this->clientList.begin(), this->clientList.end(), client);
    if (position == this->clientList.end()) {
        return;
    }
    this->sim_destroy(client->getController()->getEntity());
    client->getController()->destroy();
    delete client->getController();
    client->setController(nullptr);
    //std::cout << "erase" << *position << std::endl;
    this->clientList.remove(*position);
    //TODO: send to simulation: destroy
}

bool Game::hasClient(const Client & client)
{
    for (auto c : clientList)
    {
        if (c == &client)
            return (true);
    }
    return (false);
}

bool Game::empty()
{
    return (clientList.empty());
}

std::vector<Entity *>::iterator Game::vect_erase(std::vector<Entity *>::iterator it, std::vector<Entity*> & vect)
{
    if (it == vect.end())
    {
        return (vect.erase(it));
    }

    *it = vect.back();
    vect.pop_back();
    return (it);
}

pos_t Game::fx(size_t i)
{
    return (entities[i]->data.getPosX() + entities[i]->data.getVectX());
}

pos_t Game::fy(size_t i)
{
    return (entities[i]->data.getPosY() + entities[i]->data.getVectY());
}

pos_t Game::fxp(size_t i)
{
    return (entities[i]->data.getPosX() + entities[i]->data.getSprite().sizeX + entities[i]->data.getVectX());
}

pos_t Game::fyp(size_t i)
{
    return (entities[i]->data.getPosY() + entities[i]->data.getSprite().sizeY + entities[i]->data.getVectY());
}

void Game::sendData() {
    INFO("Game::sendData : " << this->gameEvents.size() << " events to send");
    for (auto & event : gameEvents)
    {
        auto packet = event->createPacket();
        for (auto & client : clientList)
        {
            packetf.send(*packet, client->getClientId());
        }
        delete packet;
    }
    this->gameEvents.clear();

    sendAllMoves();

    if (round - lastSyn > ROUNDS_BETWEEN_SYN)
        sendPacketSync(nullptr);
}

void Game::sim_spawn(Entity *entity) {
    this->gameEvents.push_back(new server::event::Spawn
                                       (this->round, entity->data.getId(), entity->data.getPosX(), entity->data.getPosY(), entity->data.getHp(), entity->data.getSprite().path));
    INFO("spawn " << std::to_string(gameEvents.back()->getEntityId()))
}

void Game::sim_move(Entity *entity) {
/*
    this->gameEvents.push_back(new server::event::Move(this->round, entity->data.getId(), entity->data.getVectX(),
                                                       entity->data.getVectY(), entity->data.getPosX(),
                                                       entity->data.getPosY()));
*/
}

void Game::sim_update(Entity *entity) {
    this->gameEvents.push_back(new server::event::ModHP(this->round, entity->data.getId(), entity->data.getHp()));
}

void Game::sim_destroy(Entity *entity) {
    this->gameEvents.push_back(new server::event::Destroy(this->round, entity->data.getId()));
}

uint16_t Game::getClientSize() {
    return this->clientList.size();
}

round_t Game::getTick()
{
    return (round);
}

void Game::sendPacketSync(const Client * client)
{
    auto packet_syn = new network::packet::PacketSynchronization();
    packet_syn->setTick(round);
    packet_syn->setTime(static_cast<int64_t>(std::time(nullptr)));
    if (client == nullptr)
    {
        lastSyn = round;
        for (auto client_it : clientList)
        {
            packetf.send(*packet_syn, client_it->getClientId());
        }
    }
    else
    {
        packetf.send(*packet_syn, client->getClientId());
    }
    delete packet_syn;
}

void Game::greetNewPlayer(const Client & client)
{
    auto packetPlayerData = new network::packet::PacketPlayerData();
    packetPlayerData->setNbAttack(1);
    packetPlayerData->setPlayerId(client.getController()->getEntity()->data.getId());
    packetf.send(*packetPlayerData, client.getClientId());
    delete packetPlayerData;

    sendPacketSync(&client);
    if (clientList.size() > 1) //if not first client
        sendSimToNewNotFirst(client);
}

void Game::sendSimToNewNotFirst(const Client &client)
{
    //TODO
    //this is temporary
    //do this correctly when the simulation is done

    int id = 0;
    for (auto entity : entities)
    {
        auto pspawn = new network::packet::PacketSpawnEntity();
        pspawn->setTick(round);
        pspawn->setEventId(id);
        pspawn->setEntityId(entity->data.getId());
        pspawn->setHp(entity->data.getHp());
        pspawn->setSpriteName(entity->data.getSprite().path);
        pspawn->setPosX(entity->data.getPosX());
        pspawn->setPosY(entity->data.getPosY());
        packetf.send(*pspawn, client.getClientId());
        delete pspawn;
        ++id;

        /*auto pmove = new network::packet::PacketMoveEntity();
        pmove->setTick(round);
        pmove->setEventId(id);
        pmove->setEntityId(entity->data.getId());
        pmove->setPosX(entity->data.getPosX());
        pmove->setPosY(entity->data.getPosY());
        pmove->setVecX(entity->data.getVectX());
        pmove->setVecY(entity->data.getVectY());
        packetf.send(*pmove, client.getClientId());
        delete pmove;
        ++id;*/
    }
}

void Game::sendAllMoves()
{
    //TODO
    for (auto client : clientList)
    {
        for (auto entity : entities)
        {
            auto pmove = new network::packet::PacketMoveEntity();
            pmove->setTick(round);
            pmove->setEventId(0);
            pmove->setEntityId(entity->data.getId());
            pmove->setPosX(entity->data.getPosX());
            pmove->setPosY(entity->data.getPosY());
            pmove->setVecX(entity->data.getVectX());
            pmove->setVecY(entity->data.getVectY());
            if (entity->data.getId() == 0)
            {
                std::cout << "player: " << std::to_string(entity->data.getVectX()) << " " << std::to_string(entity->data.getVectY()) << std::endl;
            }
            packetf.send(*pmove, client->getClientId());
            delete pmove;
        }
    }
}

void Game::sendSound(const std::string &soundfile)
{
    auto packet = new network::packet::PacketPlaySound();
    packet->setTick(round);
    packet->setEventId(0);
    /*packet->setSoundName(soundfile);*/ //TODO
    for (auto client : clientList)
    {
        packetf.send(*packet, client->getClientId());
    }
    delete (packet);
}

bool Game::isFinished()
{
    if (lvl->isOver(round))
    {
        for (auto entity : entities)
        {
            if (entity->data.getTeam() == FOE)
                return (false);
        }
        return (true);
    }
    else
    {
        return (false);
    }
}

void Game::endGame()
{
    std::vector<std::pair<uint32_t, std::string>> vect;
    //TODO: scores

    network::packet::PacketLeaderBoard packet(vect);
    for (auto client : clientList)
    {
        packetf.send(packet, client->getClientId());
    }
    going = false;
}

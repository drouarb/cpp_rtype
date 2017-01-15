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
#include <network/packet/PacketQuit.hh>
#include <helpers/Epoch.hh>
#include <network/packet/PacketGameData.hh>
#include <helpers/libloader/getDlLoader.hpp>
#include <network/packet/PacketUpdateEntity.hh>
#include "Game.hh"

using namespace server;

Game::Game(network::PacketFactory &packetf, int lobbyId) : packetf(packetf), lvl(nullptr), round(0), gameId(lobbyId),
                                                           entityIdCount(0), lastSyn(0), going(true), currentGamedata(nullptr), player(0)
{}

Game::Game(network::PacketFactory &packetf, int lobbyId, const Level &lvl) : packetf(packetf), lvl(&lvl), round(0),
                                                                             gameId(lobbyId), entityIdCount(0),
                                                                             lastSyn(0), going(true), currentGamedata(nullptr), player(0)
{}

Game::~Game()
{
    while (clientList.size() > 0)
    {
        removePlayer(clientList.back());
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
    manageNewGamedata();

    sendData();
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
            Entity * entity = spawn.trigger(entityIdCount, round, grid);
            if (entity == nullptr)
            {
                LOG_ERROR("Game " << gameId << ": failed to create player " << spawn.dlName << std::endl);
            }
            else
            {
                INFO("Game " << gameId << ": Adding new player(" << spawn.dlName << " on: " << entity->data.getPosX() << ", " << entity->data.getPosY());
                entityIdCount++;
                spawnEntity(entity);
            }
        }
    }
}

void Game::checkCollisions()
{
    for (auto entity : entities)
    {
        int y = grid.getCoordinate(entity->data.getPosY());
        int x = grid.getCoordinate(entity->data.getPosX());
        checkCollisionsCell(entity, y + 1, x + 1);
        checkCollisionsCell(entity, y, x + 1);
        checkCollisionsCell(entity, y - 1, x + 1);
        checkCollisionsCell(entity, y + 1, x);
        checkCollisionsCell(entity, y, x);
        checkCollisionsCell(entity, y - 1, x);
        checkCollisionsCell(entity, y + 1, x - 1);
        checkCollisionsCell(entity, y, x - 1);
        checkCollisionsCell(entity, y - 1, x - 1);
    }
}

void Game::checkCollision(Entity * entity_i, Entity * entity_j)
{
    //TODO: lighten code

    if (entity_i->collisions.includes(entity_j))
        return;
    if (entity_i->obj->collidesWith(*entity_j) == T_FALSE && entity_j->obj->collidesWith(*entity_i) == T_FALSE)
        return;
    if (entity_i->obj->collidesWith(*entity_j) == NA || entity_j->obj->collidesWith(*entity_i) == NA)
        return;

    int dist;

    // calculations are based on entity[i]

    // --- x axis

    // - left edge
    if (entity_j->data.getPosX() < entity_i->data.getPosX() &&
            !(fyp(entity_i) <= fy(entity_j) || fy(entity_i) >= fyp(entity_j)))
    {
        dist = fx(entity_i) - fxp(entity_j);
        if (dist <= 0)
        {
            if (entity_i->collisions.includes(entity_j) == false)
                entity_i->obj->collide(*entity_j, this->round);
            entity_i->collisions.add(X, NEG, entity_j);
        }
        if (dist < 0)
        {
            if (entity_i->data.getVectX() <= 0)
            {
                if (dist >= entity_i->data.getVectX())
                {
                    entity_i->data.setVectX(entity_i->data.getVectX() - dist);
                    this->sim_move(entity_i);
                    dist = 0;
                }
                else
                {
                    dist -= entity_i->data.getVectX();
                    entity_i->data.setVectX(0);
                    this->sim_move(entity_i);
                }
            }
            if (entity_j->data.getVectX() >= 0)
            {
                if (-dist <= entity_j->data.getVectX())
                {
                    entity_j->data.setVectX(entity_j->data.getVectX() - -dist);
                    this->sim_move(entity_i);
                }
                else
                {
                    entity_j->data.setVectX(0);
                    this->sim_move(entity_i);
                }
            }
        }
    }

    // - right edge
    else if (entity_j->data.getPosX() > entity_i->data.getPosX() &&
            !(fyp(entity_i) <= fy(entity_j) || fy(entity_i) >= fyp(entity_j)))
    {
        dist = fx(entity_j) - fxp(entity_i);
        if (dist <= 0)
        {
            if (entity_i->collisions.includes(entity_j) == false)
                entity_i->obj->collide(*entity_j, this->round);
            entity_i->collisions.add(X, POS, entity_j);
        }
        if (dist < 0)
        {
            if (entity_j->data.getVectX() <= 0)
            {
                if (dist >= entity_j->data.getVectX())
                {
                    entity_j->data.setVectX(entity_j->data.getVectX() - dist);
                    this->sim_move(entity_i);
                    dist = 0;
                }
                else
                {
                    dist -= entity_j->data.getVectX();
                    entity_j->data.setVectX(0);
                    this->sim_move(entity_i);
                }
            }
            if (entity_i->data.getVectX() >= 0)
            {
                if (-dist <= entity_i->data.getVectX())
                {
                    entity_i->data.setVectX(entity_i->data.getVectX() - -dist);
                    this->sim_move(entity_i);
                }
                else
                {
                    entity_i->data.setVectX(0);
                    this->sim_move(entity_i);
                }
            }
        }
    }

    // --- y axis

    // - upper edge
    if (entity_j->data.getPosY() < entity_i->data.getPosY() &&
            !(fxp(entity_i) <= fx(entity_j) || fx(entity_i) >= fxp(entity_j)))
    {
        dist = fy(entity_i) - fyp(entity_j);
        if (dist <= 0)
        {
            if (entity_i->collisions.includes(entity_j) == false)
                entity_i->obj->collide(*entity_j, this->round);
            entity_i->collisions.add(Y, NEG, entity_j);
        }
        if (dist < 0)
        {
            if (entity_i->data.getVectY() <= 0)
            {
                if (dist >= entity_i->data.getVectY())
                {
                    entity_i->data.setVectY(entity_i->data.getVectY() - dist);
                    this->sim_move(entity_i);
                    dist = 0;
                }
                else
                {
                    dist -= entity_i->data.getVectY();
                    entity_i->data.setVectY(0);
                    this->sim_move(entity_i);
                }
            }
            if (entity_j->data.getVectY() >= 0)
            {
                if (-dist <= entity_j->data.getVectY())
                {
                    entity_j->data.setVectY(entity_j->data.getVectY() - -dist);
                    this->sim_move(entity_i);
                }
                else
                {
                    entity_j->data.setVectY(0);
                    this->sim_move(entity_i);
                }
            }
        }
    }

    // - lower edge
    else if (entity_j->data.getPosY() > entity_i->data.getPosY() &&
            !(fxp(entity_i) <= fx(entity_j) || fx(entity_i) >= fxp(entity_j)))
    {
        dist = fy(entity_j) - fyp(entity_i);
        if (dist <= 0)
        {
            if (entity_i->collisions.includes(entity_j) == false)
                entity_i->obj->collide(*entity_j, this->round);
            entity_i->collisions.add(Y, POS, entity_j);
        }
        if (dist < 0)
        {
            if (entity_j->data.getVectY() <= 0)
            {
                if (dist >= entity_j->data.getVectY())
                {
                    entity_j->data.setVectY(entity_j->data.getVectY() - dist);
                    this->sim_move(entity_i);
                    dist = 0;
                }
                else
                {
                    dist -= entity_j->data.getVectY();
                    entity_j->data.setVectY(0);
                    this->sim_move(entity_i);
                }
            }
            if (entity_i->data.getVectY() >= 0)
            {
                if (-dist <= entity_i->data.getVectY())
                {
                    entity_i->data.setVectY(entity_i->data.getVectY() - -dist);
                    this->sim_move(entity_i);
                }
                else
                {
                    entity_i->data.setVectY(0);
                    this->sim_move(entity_i);
                }
            }
        }
    }
}

void Game::letEntitesAct()
{
    for (size_t i = 0; i != entities.size(); ++i)
    {
        auto it = entities.at(i);
        EntityAction * action = it->obj->act(this->round, grid);
        act(action, &*it);
        delete action;
    }
}

void Game::act(EntityAction *action, Entity *entity)
{
    if (entity->collisions.isSet())
    {
        entity->collisions.apply(action);
        entity->collisions.reset();
    }

    if (action->speedX != entity->data.getVectX())
    {
        entity->data.setVectX(action->speedX);
        this->sim_move(entity);
    }
    if (action->speedY != entity->data.getVectY())
    {
        entity->data.setVectY(action->speedY);
        this->sim_move(entity);
    }
    if (action->hp != entity->data.getHp())
    {
        entity->data.setHp(action->hp);
        this->sim_update(entity);
    }
    if (action->newEntity)
    {
        auto newEntity = new Entity(action->newEntity, entityIdCount, round, grid);
        entityIdCount++;
        spawnEntity(newEntity);

        auto init = newEntity->obj->initialize(round, grid);
        act(&init->action, newEntity);
        delete init;
    }
    if (action->destroy)
    {
        entity->data.setDestroyed(true);
    }
    if (action->soundToPlay != "")
    {
        sendSound(action->soundToPlay);
    }
}

void Game::moveEntities()
{
    for (auto entity : entities)
    {
        bool change = willChangeCell(entity);
        if (change)
            grid.remove(entity);

        entity->data.setPosX(entity->data.getPosX() + entity->data.getVectX());
        entity->data.setPosY(entity->data.getPosY() + entity->data.getVectY());

        if (change)
            grid.add(entity);
    }
}

void Game::unspawn()
{
    for (size_t i = 0; i < entities.size(); ++i)
    {
        auto it = &entities.at(i);
        if ((*it)->data.getPosX() + (*it)->data.getSprite().sizeX <= FIELD_BORDER_LEFT - LEFT_MARGIN || (*it)->data.getPosX() > FIELD_BORDER_RIGHT + RIGHT_MARGIN
                || (*it)->data.getPosY() + (*it)->data.getSprite().sizeY < Y_BORDER_WIDTH || (*it)->data.getPosY() > FIELD_HEIGHT + Y_BORDER_WIDTH)
        {
            (*it)->data.setDestroyed(true);
            INFO("OUT OF RANGE : " << (*it)->data.getId())
        }
        if ((*it)->data.isDestroyed())
        {
            INFO("delete player : " << (*it)->data.getId())
            this->sim_destroy(*it);
            destroyedEntities.push_back(*it);
            grid.remove(*it);
            entities.erase(std::find(entities.begin(), entities.end(), *it));
        }
        else
            ++it; //TODO
    }
    if (going && isFinished())
        endGame();
}

void Game::manageNewGamedata()
{
    auto gamedata = lvl->getNewData(round);
    if (gamedata != nullptr)
    {
        auto packet = network::packet::PacketGameData();
        packet.setBackground(gamedata->first);
        packet.setAudio(gamedata->second);

        for (auto client : clientList)
        {
            packetf.send(packet, client->getClientId());
        }
        currentGamedata = gamedata;
    }
}

void Game::checkCollisionsCell(Entity * entity, int cell_y, int cell_x)
{
    if (cell_y < 0 || cell_y >= GRID_HEIGHT || cell_x < 0 || cell_x >= GRID_WIDTH)
        return;
    auto & cell = grid[cell_y][cell_x];
    for (size_t j = 0; j < cell.size(); ++j)
    {
        if (cell[j]->data.getId() != entity->data.getId())
        {
            checkCollision(entity, cell[j]);
        }
    }
}

bool Game::willChangeCell(const Entity * entity)
{
    auto old = grid.getCoordinate(entity->data.getPosX());
    if (grid.getCoordinate(entity->data.getPosX() + entity->data.getVectX()) != old)
        return (true);
    old = grid.getCoordinate(entity->data.getPosY());
    return (grid.getCoordinate(entity->data.getPosY() + entity->data.getVectY()) != old);
}



void Game::spawnEntity(Entity * entity)
{
    entities.push_back(entity);
    this->sim_spawn(entity);
    this->sim_move(entity);
    grid.add(entity);
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
    Entity *entity = new Entity();
    controller->setEntity(entity);
    entity->initialize(getDlLoader<ADynamicObject>(playerPaths[this->player++])->getInstance(), entityIdCount, round, grid);
    this->player %= 4;
    entityIdCount++;
    controller->setEntity(static_cast<Player *>(entity->obj));
    client->setController(controller);
    spawnEntity(entity);
    greetNewPlayer(*client);
}

void Game::removePlayer(Client *client)
{
    this->player -= 1;
    this->player = this->player < 0 ? 0 : this->player;
    const std::list<server::Client *>::iterator &position = std::find(this->clientList.begin(), this->clientList.end(), client);
    if (position == this->clientList.end())
    {
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

bool Game::empty() const
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

pos_t Game::fx(const Entity * entity_i) const
{
    return (entity_i->data.getPosX() + entity_i->data.getVectX());
}

pos_t Game::fy(const Entity * entity_i) const
{
    return (entity_i->data.getPosY() + entity_i->data.getVectY());
}

pos_t Game::fxp(const Entity * entity_i) const
{
    return (entity_i->data.getPosX() + entity_i->data.getSprite().sizeX + entity_i->data.getVectX());
}

pos_t Game::fyp(const Entity * entity_i) const
{
    return (entity_i->data.getPosY() + entity_i->data.getSprite().sizeY + entity_i->data.getVectY());
}

void Game::sendData() {
    INFO("Game::sendData : " << this->gameEvents.size() << " events to send");

    for (auto & event : gameEvents)
    {
        if (event->getEntity()->data.isDestroyed() && event->getEventType() != event::DESTROY)
            continue;

        if (event->getEntity()->data.getId() == 0)
        {
            if (event->getEventType() == event::MOVE)
            {
                auto m = dynamic_cast<network::packet::PacketMoveEntity*>(event->createPacket());
                std::cout << "vx=" << m->getVecX() << " vy=" << m->getVecY() << std::endl;
            }
            if (event->getEventType() == event::MOD_HP)
            {
                auto m = dynamic_cast<network::packet::PacketUpdateEntity*>(event->createPacket());
                std::cout << "hp=" << m->getHp() << std::endl;
            }
            if (event->getEventType() == event::DESTROY)
            {
                std::cout << "destroy" << std::endl;
            }
            if (event->getEventType() == event::SPAWN)
            {
                auto m = dynamic_cast<network::packet::PacketSpawnEntity*>(event->createPacket());
                std::cout << "spawn hp=" << m->getHp() << std::endl;
            }
        }

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
                                       (this->round, entity, entity->data.getPosX(), entity->data.getPosY(), entity->data.getHp(), entity->data.getSprite().path));
    INFO("spawn " << std::to_string(gameEvents.back()->getEntity()))
}

void Game::sim_move(Entity *entity)
{
    this->gameEvents.push_back(new server::event::Move(this->round, entity, entity->data.getVectX(),
                                                       entity->data.getVectY(), entity->data.getPosX(),
                                                       entity->data.getPosY()));
}

void Game::sim_update(Entity *entity) {
    this->gameEvents.push_back(new server::event::ModHP(this->round, entity, entity->data.getHp()));
}

void Game::sim_destroy(Entity *entity) {
    this->gameEvents.push_back(new server::event::Destroy(this->round, entity));
}

uint16_t Game::getClientSize() const
{
    return static_cast<uint16_t >(this->clientList.size());
}

round_t Game::getTick() const
{
    return (round);
}

bool Game::mustClose() const
{
    return (!going || empty());
}

void Game::sendPacketSync(const Client * client)
{
    auto packet_syn = new network::packet::PacketSynchronization();
    packet_syn->setTick(round);
    packet_syn->setTime(static_cast<int64_t>(helpers::Epoch::getTimeMs()));
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
    auto packetPlayerData = network::packet::PacketPlayerData();
    packetPlayerData.setNbAttack(1);
    packetPlayerData.setPlayerId(client.getController()->getEntity()->data.getId());
    packetf.send(packetPlayerData, client.getClientId());

    if (currentGamedata != nullptr)
    {
        auto packetGameData = network::packet::PacketGameData();
        packetGameData.setBackground(currentGamedata->first);
        packetGameData.setAudio(currentGamedata->second);
        packetf.send(packetGameData, client.getClientId());
    }

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
        pspawn->setPosX(entity->data.getPosX() * 100.0);
        pspawn->setPosY(entity->data.getPosY() * 100.0);
        packetf.send(*pspawn, client.getClientId());
        delete pspawn;
        ++id;

        auto pmove = new network::packet::PacketMoveEntity();
        pmove->setTick(round);
        pmove->setEventId(id);
        pmove->setEntityId(entity->data.getId());
        pmove->setPosX(entity->data.getPosX() * 100.0);
        pmove->setPosY(entity->data.getPosY() * 100.0);
        pmove->setVecX(entity->data.getVectX() * 100.0);
        pmove->setVecY(entity->data.getVectY() * 100.0);
        packetf.send(*pmove, client.getClientId());
        delete pmove;
        ++id;
    }
}

void Game::sendAllMoves()
{
    //TODO
  if (round % 120 == 0)
    for (auto client : clientList)
    {
        for (auto entity : entities)
        {
            auto pmove = new network::packet::PacketMoveEntity();
            pmove->setTick(round);
            pmove->setEventId(0);
            pmove->setEntityId(entity->data.getId());
            pmove->setPosX(entity->data.getPosX() * 100.0);
            pmove->setPosY(entity->data.getPosY() * 100.0);
            pmove->setVecX(entity->data.getVectX() * 100.0);
            pmove->setVecY(entity->data.getVectY() * 100.0);

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
    packet->setSoundName(soundfile);

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
            {
                return (false);
            }
        }
        return (true);
    }
    else
    {
        return (false);
    }
}

bool scoreComp(const std::pair<uint32_t, std::string> & a, const std::pair<uint32_t, std::string> & b)
{
    return (a.first < b.first);
}

void Game::endGame()
{
    std::vector<std::pair<uint32_t, std::string>> vect;
    for (auto client : clientList)
    {
        if (client->getName() != "")
        {
            vect.push_back(std::pair<uint32_t, std::string>(client->getController()->getPlayer()->getScore(), client->getName()));
        }
    }

    std::sort(vect.begin(), vect.end(), &scoreComp);

    std::cout << "SCORES" << std::endl;
    for (auto it : vect)
    {
        std::cout << it.second << " -> " << std::to_string(it.first) << std::endl;
    }

    network::packet::PacketLeaderBoard packetscore(vect);
    network::packet::PacketQuit packetquit;
    for (auto client : clientList)
    {
        packetf.send(packetscore, client->getClientId());
        packetf.send(packetquit, client->getClientId());
    }
    going = false;
}

const std::string Game::playerPaths[4] =
    {
            "build/entity/YellowPlayer",
            "build/entity/BluePlayer",
            "build/entity/GreenPlayer",
            "build/entity/RedPlayer"
    };

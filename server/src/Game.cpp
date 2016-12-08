#include <algorithm>
#include <iostream>
#include <LibLoader/IDlLoader.hh>
#include "Game.hh"

using namespace server;

Game::Game(int lobbyId) : lvl(nullptr), gameId(lobbyId)
{
    //this->entities.reserve(256);
    //Create vector with 256 nullptr, causes SIGSEV on all iteration
}

Game::Game(int lobbyId, const Level & lvl) : lvl(&lvl), entities(256), gameId(lobbyId)
{ }

Game::~Game()
{ }

void Game::setLevel(const Level & lvl)
{
    this->lvl = &lvl;
}

void Game::tick(round_t round)
{
    this->round = round;
    progressLevel();
    letEntitesAct();
    checkCollisions();
    moveEntities();
    unspawn();
    //TODO: send packets to client
}

int Game::getLobbyId()
{
    return (gameId);
}

void Game::progressLevel()
{
    if (lvl)
    {
        const std::vector<Spawn> *pVector = lvl->getNewSpawns(round);
        if (pVector == NULL) {
            return;
        }
        for (auto spawn : *pVector)
        {
            IEntity * entity = spawn.trigger();
            if (entity == nullptr)
            {
                std::cerr << "Game " << gameId << ": failed to create entity " << spawn.dlName + DLL_EXTENSION << std::endl;
            }
            else
            {
                entities.push_back(spawn.trigger());
            }
        }
    }
}

void Game::checkCollisions()
{
    //TODO
    //
}

void Game::letEntitesAct()
{
    for (auto entity : entities)
    {
        if (!entity) {
            return;
        }
        if (!entity->isDestroyed()){}
        {
            auto action = entity->nextAction();
            if (action->destroy)
                entity->destroy();
            if (action->newEntity)
                entities.push_back(action->newEntity);
        }
    }
}

void Game::moveEntities()
{
    for (auto entity : entities)
    {
        if (!entity) {
            return;
        }
        entity->setPosX(entity->getPosX() + entity->getSpeedX());
        entity->setPosY(entity->getPosY() + entity->getSpeedY());
        //TODO: do this in checkCollisions, by changing the vectors?
        if (entity->getPosY() > FIELD_HEIGHT)
            entity->setPosY(FIELD_HEIGHT);
        if (entity->getPosY() < 0)
            entity->setPosY(0);
        if (entity->getPosX() < FIELD_BORDER_LEFT - LEFT_MARGIN)
            entity->setPosX(FIELD_BORDER_LEFT - LEFT_MARGIN);
        if (entity->getPosX() > FIELD_BORDER_RIGHT + RIGHT_MARGIN)
            entity->setPosX(FIELD_BORDER_RIGHT + RIGHT_MARGIN);
    }
}

void Game::unspawn()
{
    for (auto entity : entities)
    {
        if (!entity) {
            return;
        }
        if (entity->getPosX() <= FIELD_BORDER_LEFT - LEFT_MARGIN){}
        {
            entity->destroy();
        }
    }
}

void Game::newPlayer(Client *client) {
    if (clientList.size() == 4) {
        throw std::runtime_error("Cannot add more than 4 player in a game");
    }
    this->clientList.push_back(client);
}

void Game::removePlayer(Client *client) {
    const std::list<server::Client *>::const_iterator &position = std::find(this->clientList.begin(), this->clientList.end(), client);
    if (position == this->clientList.end()) {
        return;
    }
    this->clientList.erase(position);
}
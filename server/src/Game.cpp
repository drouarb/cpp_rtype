#include <iostream>
#include "Game.hh"

using namespace server;

Game::Game(int lobbyId) : lvl(nullptr), entities(256), gameId(lobbyId)
{ }

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
        for (auto spawn : *pVector)
        {
            IEntity * entity = spawn.trigger();
            if (entity == nullptr)
            {
                std::cerr << "Game " << gameId << ": failed to create entity " << spawn.dlName << std::endl;
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
        if (!entity->isDestroyed())
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
        if (entity->getPosX() <= FIELD_BORDER_LEFT - LEFT_MARGIN)
        {
            entity->destroy();
        }
    }
}
#include "Game.hh"

using namespace server;

Game::Game() : lvl(nullptr), entities(256)
{ }

Game::Game(const Level & lvl) : lvl(&lvl), entities(256)
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
    checkCollisions();
    letEntitesAct();
    moveEntities();
    //TODO: how will packets be sent? ref to packetfactory? intermediate class?
}

void Game::progressLevel()
{
    if (lvl)
    {
        for (auto spawn : lvl->getNewSpawns(round))
        {
            entities.push_back(spawn.trigger());
        }
    }
}

void Game::checkCollisions()
{
    //TODO
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
    }
}


#include <algorithm>
#include <iostream>
#include <LibLoader/IDlLoader.hh>
#include <Player.hh>
#include "Game.hh"
#include "../../Entities/include/BasicEntity.hh"

using namespace server;

Game::Game(int lobbyId) : lvl(nullptr), gameId(lobbyId), entityIdCount(0)
{ }

Game::Game(int lobbyId, const Level & lvl) : lvl(&lvl), gameId(lobbyId), entityIdCount(0)
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
        if (pVector == NULL)
        {
            return;
        }
        for (auto spawn : *pVector)
        {
            IEntity * entity = spawn.trigger();
            if (entity == nullptr)
            {
                std::cerr << "Game " << gameId << ": failed to create entity " << spawn.dlName << std::endl;
            }
            else
            {
                entity->setEntityId(entityIdCount);
                std::cout << entity->getPosX() << ", " << entity->getPosY();
                entityIdCount++;
                entities.push_front(entity);
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
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        auto action = (*it)->nextAction();
        if (action->newEntity)
        {
            entities.push_back(action->newEntity);
        }
        if (action->destroy)
        {
            (*it)->destroy();
        }
        delete action;
    }
}

void Game::moveEntities()
{
    for (auto entity : entities)
    {
        entity->setPosX(entity->getPosX() + entity->getSpeedX());
        entity->setPosY(entity->getPosY() + entity->getSpeedY());
        std::cout << "entity " << std::to_string(entity->getEntityId()) << " x=" << std::to_string(entity->getPosX()) << " y=" << std::to_string(entity->getPosY()) << std::endl;
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
    for (auto it = entities.begin(); it != entities.end();)
    {
        if ((*it)->getPosX() <= FIELD_BORDER_LEFT - LEFT_MARGIN)
        {
            (*it)->destroy();
        }
        if ((*it)->isDestroyed())
        {
            destroyedEntities.push_front(*it);
            it = entities.erase(it);
        }
        else
            ++it;
    }

}

void Game::newPlayer(Client *client) {
    if (clientList.size() == 4) {
        throw std::runtime_error("Cannot add more than 4 player in a game");
    }
    Controller *controller = new Controller();
    this->clientList.push_back(client);
    IEntity *player = new Player();
    player->setEntityId(entityIdCount);
    entityIdCount++;
    controller->setEntity(player);
    client->setController(controller);
    this->entities.push_back(player);
}

void Game::removePlayer(Client *client) {
    const std::list<server::Client *>::iterator &position = std::find(this->clientList.begin(), this->clientList.end(), client);
    if (position == this->clientList.end()) {
        return;
    }
    this->clientList.erase(position);
}

#include <algorithm>
#include <iostream>
#include <Player.hh>
#include "Game.hh"

using namespace server;

Game::Game(int lobbyId) : lvl(nullptr), round(0), gameId(lobbyId), entityIdCount(0)
{ }

Game::Game(int lobbyId, const Level & lvl) : lvl(&lvl), round(0), gameId(lobbyId), entityIdCount(0)
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
    letEntitesAct();
    checkCollisions();
    moveEntities();
    unspawn();
    //TODO: send packets to client
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
            Entity * entity = spawn.trigger(entityIdCount);
            if (entity == nullptr)
            {
                std::cerr << "Game " << gameId << ": failed to create entity " << spawn.dlName << std::endl;
            }
            else
            {
                std::cout << entity->data.getPosX() << ", " << entity->data.getPosY();
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
        EntityAction * action = (*it)->obj->nextAction();
        if (action->speedX != (*it)->data.getVectX())
        {
            (*it)->data.setVectX(action->speedX);
        }
        if (action->speedY != (*it)->data.getVectY())
        {
            (*it)->data.setVectY(action->speedY);
        }
        if (action->hp != (*it)->data.getHp())
        {
            (*it)->data.setHp(action->hp);
        }
        if (action->newEntity)
        {
            entities.push_back(action->newEntity);
        }
        if (action->destroy)
        {
            (*it)->data.setDestroyed(true);
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
        std::cout << "entity " << std::to_string(entity->data.getId()) << " x=" << std::to_string(entity->data.getPosX()) << " y=" << std::to_string(entity->data.getPosY()) << std::endl;
        //TODO: do this in checkCollisions, by changing the vectors?
        if (entity->data.getPosY() > FIELD_HEIGHT)
            entity->data.setPosY(FIELD_HEIGHT);
        if (entity->data.getPosY() < 0)
            entity->data.setPosY(0);
        if (entity->data.getPosX() < FIELD_BORDER_LEFT - LEFT_MARGIN)
            entity->data.setPosX(FIELD_BORDER_LEFT - LEFT_MARGIN);
        if (entity->data.getPosX() > FIELD_BORDER_RIGHT + RIGHT_MARGIN)
            entity->data.setPosX(FIELD_BORDER_RIGHT + RIGHT_MARGIN);
    }
}

void Game::unspawn()
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        if ((*it)->data.getPosX() <= FIELD_BORDER_LEFT - LEFT_MARGIN)
        {
            (*it)->data.setDestroyed(true);
        }
        if ((*it)->data.isDestroyed())
        {
            destroyedEntities.push_front(*it);
            it = entities.erase(it);
        }
        else
            ++it;
    }

}

void Game::newPlayer(Client *client) {
    if (clientList.size() == 4)
    {
        std::cout << "maximum number of players reached" << std::endl;
        return;
    }
    Controller *controller = new Controller();
    this->clientList.push_back(client);
    Player *player = new Player();
    Entity *entity = new Entity();
    entity->initialize(player, entityIdCount);
    entityIdCount++;
    controller->setEntity(player);
    client->setController(controller);
    this->entities.push_back(entity);
}

void Game::removePlayer(Client *client) {
    const std::list<server::Client *>::iterator &position = std::find(this->clientList.begin(), this->clientList.end(), client);
    if (position == this->clientList.end()) {
        return;
    }
    client->getController()->destroy();
    delete client->getController();
    client->setController(nullptr);
    std::cout << "erase" << *position << std::endl;
    this->clientList.remove(*position);
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

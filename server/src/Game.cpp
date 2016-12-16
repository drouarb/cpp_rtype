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
                entities.push_back(entity);
            }
        }
    }
}

void Game::checkCollisions()
{
    size_t max = entities.size();
    for (size_t i = 0; i < max; ++i)
    {
        for (size_t j = i + 1; j < max; ++j)
        {
            int dist;

            // calculations are based on entities[i]

            // --- x axis

            // - left edge
            if (entities[j]->data.getPosX() < entities[i]->data.getPosX() &&
                    ((fy(i) >= fy(j) && fy(i) <= fyp(j)) || (fyp(i) >= fy(j) && fyp(i) <= fyp(j))))
            {
                dist = fx(i) - fxp(j);
                std::cout << "left dist=" << std::to_string(dist) << std::endl;
                if (dist <= 0)
                {
                    entities[i]->obj->collide(*entities[j]);
                    entities[j]->obj->collide(*entities[i]);

                    if (entities[i]->data.getVectX() <= 0)
                    {
                        if (dist >= entities[i]->data.getVectX())
                        {
                            entities[i]->data.setVectX(entities[i]->data.getVectX() - dist);
                            dist = 0;
                        }
                        else
                        {
                            dist -= entities[i]->data.getVectX();
                            entities[i]->data.setVectX(0);
                        }
                    }
                    if (entities[j]->data.getVectX() >= 0)
                    {
                        if (-dist <= entities[j]->data.getVectX())
                        {
                            entities[j]->data.setVectX(entities[j]->data.getVectX() - -dist);
                        }
                        else
                        {
                            entities[j]->data.setVectX(0);
                        }
                    }
                }
            }

            // - right edge
            if (entities[j]->data.getPosX() > entities[i]->data.getPosX() &&
                ((fy(i) >= fy(j) && fy(i) <= fyp(j)) || (fyp(i) >= fy(j) && fyp(i) <= fyp(j))))
            {
                dist = fx(j) - fxp(i);
                std::cout << "right dist=" << std::to_string(dist) << std::endl;
                if (dist <= 0)
                {
                    entities[i]->obj->collide(*entities[j]);
                    entities[j]->obj->collide(*entities[i]);

                    if (entities[j]->data.getVectX() <= 0)
                    {
                        if (dist >= entities[j]->data.getVectX())
                        {
                            entities[j]->data.setVectX(entities[j]->data.getVectX() - dist);
                            dist = 0;
                        }
                        else
                        {
                            dist -= entities[j]->data.getVectX();
                            entities[j]->data.setVectX(0);
                        }
                    }
                    if (entities[i]->data.getVectX() >= 0)
                    {
                        if (-dist <= entities[i]->data.getVectX())
                        {
                            entities[i]->data.setVectX(entities[i]->data.getVectX() - -dist);
                        }
                        else
                        {
                            entities[i]->data.setVectX(0);
                        }
                    }
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
                    entities[i]->obj->collide(*entities[j]);
                    entities[j]->obj->collide(*entities[i]);

                    if (entities[i]->data.getVectY() <= 0)
                    {
                        if (dist >= entities[i]->data.getVectY())
                        {
                            entities[i]->data.setVectY(entities[i]->data.getVectY() - dist);
                            dist = 0;
                        }
                        else
                        {
                            dist -= entities[i]->data.getVectY();
                            entities[i]->data.setVectY(0);
                        }
                    }
                    if (entities[j]->data.getVectY() >= 0)
                    {
                        if (-dist <= entities[j]->data.getVectY())
                        {
                            entities[j]->data.setVectY(entities[j]->data.getVectY() - -dist);
                        }
                        else
                        {
                            entities[j]->data.setVectY(0);
                        }
                    }
                }
            }

            // - lower edge
            if (entities[j]->data.getPosY() > entities[i]->data.getPosY() &&
                ((fx(i) >= fx(j) && fx(i) <= fxp(j)) || (fxp(i) >= fx(j) && fxp(i) <= fxp(j))))
            {
                dist = fy(j) - fyp(i);
                std::cout << "down dist=" << std::to_string(dist) << std::endl;
                if (dist <= 0)
                {
                    entities[i]->obj->collide(*entities[j]);
                    entities[j]->obj->collide(*entities[i]);

                    if (entities[j]->data.getVectY() <= 0)
                    {
                        if (dist >= entities[j]->data.getVectY())
                        {
                            entities[j]->data.setVectY(entities[j]->data.getVectY() - dist);
                            dist = 0;
                        }
                        else
                        {
                            dist -= entities[j]->data.getVectY();
                            entities[j]->data.setVectY(0);
                        }
                    }
                    if (entities[i]->data.getVectY() >= 0)
                    {
                        if (-dist <= entities[i]->data.getVectY())
                        {
                            entities[i]->data.setVectY(entities[i]->data.getVectY() - -dist);
                        }
                        else
                        {
                            entities[i]->data.setVectY(0);
                        }
                    }
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
        EntityAction * action = it->obj->nextAction();
        if (action->speedX != it->data.getVectX())
        {
            it->data.setVectX(action->speedX);
        }
        if (action->speedY != it->data.getVectY())
        {
            it->data.setVectY(action->speedY);
        }
        if (action->hp != it->data.getHp())
        {
            it->data.setHp(action->hp);
        }
        if (action->newEntity)
        {
            entities.push_back(new Entity(action->newEntity, entityIdCount));
            entityIdCount++;
        }
        if (action->destroy)
        {
            it->data.setDestroyed(true);
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
            destroyedEntities.push_back(*it);
            it = vect_erase(it, entities);
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

pos_t Game::fx(int i)
{
    return (entities[i]->data.getPosX() + entities[i]->data.getVectX());
}

pos_t Game::fy(int i)
{
    return (entities[i]->data.getPosY() + entities[i]->data.getVectY());
}

pos_t Game::fxp(int i)
{
    return (entities[i]->data.getPosX() + entities[i]->data.getSprite().sizeX + entities[i]->data.getVectX());
}

pos_t Game::fyp(int i)
{
    return (entities[i]->data.getPosY() + entities[i]->data.getSprite().sizeY + entities[i]->data.getVectY());
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

//
// Created by greg on 02/12/2016.
//

#include <definitions.hh>
#include <Player.hh>
#include <iostream>
#include "Entity.hh"

using namespace server;

void Player::shoot(attackId_t attackId)
{
    this->attackQueue.push(attackId);
}

Player::Player() : mustDestroy(false), vectX(0), vectY(0)
{ }

void Player::collide(const Entity &entity)
{
    std::cout << "Player " << this->data->getId() << " collides with entity id " << entity.data.getId() << std::endl;
}

EntityAction * Player::nextAction()
{
    if (!attackQueue.empty())
        std::cout << "shoot: " << std::to_string(attackQueue.back()) << std::endl;
    while (!attackQueue.empty())
        attackQueue.pop();
    EntityAction * act = new EntityAction();
    if (mustDestroy)
    {
        act->destroy = true;
    }
    act->speedX = vectX;
    act->speedY = vectY;
    return act;
}

EntityInitialization * Player::initialize()
{
    EntityInitialization * ei = new EntityInitialization();
    ei->team = PLAYER;
    ei->action.hp = 5;
    ei->posX = 0;
    ei->posY = FIELD_HEIGHT / 2;
    return (ei);
}

damage_t Player::getDamage()
{
    return (0);
}

void Player::move(speed_t vectX, speed_t vectY)
{
    this->vectX = vectX;
    this->vectY = vectY;
}

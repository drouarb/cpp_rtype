//
// Created by greg on 02/12/2016.
//

#include <definitions.hh>
#include <Player.hh>
#include <iostream>

void server::Player::shoot(server::attackId_t attackId) {
    this->attackQueue.push(attackId);
}

server::Player::Player() :  id(0), team(server::PLAYER), sprite(""), posX(0), posY(FIELD_HEIGHT / 2), speedX(0), speedY(0), hp(-1), destroyed(false), mustDestroy(false)
{}

void server::Player::setEntityId(server::entityId_t id)
{
    this->id = id;
}

server::entityId_t server::Player::getEntityId()
{
    return id;
}

server::Team server::Player::getTeam()
{
    return team;
}

std::string &server::Player::getSprite()
{
    return sprite;
}

void server::Player::setPosX(server::pos_t pos)
{
    this->posX = pos;
}

void server::Player::setPosY(server::pos_t pos)
{
    this->posY = pos;
}

server::pos_t server::Player::getPosX()
{
    return posX;
}

server::pos_t server::Player::getPosY()
{
    return posY;
}

void server::Player::setSpeedX(server::speed_t sp)
{
    this->speedX = sp;
}

server::speed_t server::Player::getSpeedX()
{
    return speedX;
}

void server::Player::setSpeedY(server::speed_t sp)
{
    this->speedY = sp;
}

server::speed_t server::Player::getSpeedY()
{
    return this->speedY;
}

void server::Player::modHp(int m)
{
    this->hp += m;
}

int server::Player::getHp()
{
    return (hp);
}

void server::Player::destroy()
{
    this->destroyed = true;
}

void server::Player::restore()
{
    this->destroyed = false;
}

bool server::Player::isDestroyed()
{
    return destroyed;
}

void server::Player::collide(server::IEntity *entity)
{
    std::cout << "Player " << this->id << " collide with entity id " << entity->getEntityId() << std::endl;
}

server::EntityAction *server::Player::nextAction()
{
    std::cout << "shoot: " << std::to_string(attackQueue.back()) << std::endl;
    while (!attackQueue.empty())
        attackQueue.pop();
    EntityAction * act = new EntityAction();
    if (mustDestroy)
        act->destroy = true;
    return act;
}

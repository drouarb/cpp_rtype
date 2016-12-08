//
// Created by greg on 02/12/2016.
//

#include <definitions.hh>
#include <Player.hh>

void server::Player::shoot(server::attackId_t attackId) {
    //TODO
}

server::Player::Player() {}

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

void server::Player::collide(server::IEntity *)
{

}

server::EntityAction *server::Player::nextAction()
{
    return new EntityAction();
}

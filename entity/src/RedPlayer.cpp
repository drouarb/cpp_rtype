//
// Created by greg on 22/12/16.
//

#include <entities/Entity.hh>
#include <iostream>
#include "RedPlayer.hh"

server::EntityInitialization *RedPlayer::initialize(server::round_t r, const server::Grid &e) {
    server::EntityInitialization *pInitialization = server::Player::initialize(r, e);
    pInitialization->sprite.path = "media/sprites/magicalGirlA.png";
    return pInitialization;
}

server::ADynamicObject *RedPlayer::createAttack(server::attackId_t id, server::round_t round)
{
    if (id == 1)
    {
        setAttackWait(id, 30, round);
        return new RegenMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40, this->data->getPosY() + 10);
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40, this->data->getPosY() + 10,
                                "media/sprites/daggerA.png");
    }
}




RedPlayer::RegenMissile::RegenMissile(server::APlayer * owner, server::pos_t posX, server::pos_t posY) :
        Power(owner), posX(posX), posY(posY) {}

server::EntityInitialization *RedPlayer::RegenMissile::initialize(server::round_t, const server::Grid &environment) {
    this->mustDestroy = false;
    server::EntityInitialization *initialization = new server::EntityInitialization;
    initialization->posY = this->posY;
    initialization->posX = this->posX;
    initialization->sprite = std::string("media/sprites/crystalA.png");
    initialization->action.speedX = 10;
    initialization->action.speedY = 0;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 21;
    initialization->sprite.sizeY = 11;
    return initialization;
}

void RedPlayer::RegenMissile::collide(const server::Entity &entity, server::round_t)
{
    if (entity.data.getTeam() == server::PLAYER)
    {
        modScore(static_cast<server::score_t >(2 * getDamage()));
    }
    this->mustDestroy = true;
}

server::EntityAction *RedPlayer::RegenMissile::act(server::round_t current_round, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();
    action->speedX = 10;
    action->speedY = 0;
    action->destroy = this->mustDestroy;
    return action;
}

server::hp_t RedPlayer::RegenMissile::getDamage() {
    return -20;
}

server::Tribool RedPlayer::RegenMissile::collidesWith(const server::Entity &entity) {
    if (entity.data.getId() == getOwner()->data->getId())
    {
        return (server::T_FALSE);
    }
    return (entity.data.getTeam() == server::PLAYER ? server::T_TRUE : server::T_FALSE);
}






extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new RedPlayer());
}
}

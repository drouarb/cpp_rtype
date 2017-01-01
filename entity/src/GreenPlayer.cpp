//
// Created by greg on 22/12/16.
//

#include <iostream>
#include <entities/Entity.hh>
#include "GreenPlayer.hh"

server::EntityInitialization *GreenPlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlD.png";
    return pInitialization;
}

server::ADynamicObject *GreenPlayer::createAttack(server::attackId_t id, server::round_t round)
{
    if (id == 1)
    {
        setAttackWait(id, 20, round);
        return new WallAttack(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                              this->data->getPosY() + 10);
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40, this->data->getPosY() + 10,
                                "media/sprites/daggerD.png");
    }
}

/*
 * ----------------------------------------------------------------------------------------------------------
 */

GreenPlayer::WallAttack::WallAttack(server::APlayer *owner, server::pos_t posX, server::pos_t posY)
        : Power(owner), posX(posX), posY(posY), initialRound(0)
{}

void GreenPlayer::WallAttack::collide(const server::Entity &entity, server::round_t current_round) {}

server::EntityAction *
GreenPlayer::WallAttack::act(server::round_t current_round, const server::Grid &vector)
{
    server::EntityAction *entityAction = new server::EntityAction();

    if (current_round - initialRound >= 2 * WALL_SIZE)
    {
        entityAction->destroy = true;
        return (entityAction);
    }

    if (current_round - initialRound == 1)
    {
        entityAction->newEntity = new WallElement(this->posX, this->posY, getOwner());
    }
    else if (current_round - initialRound > 1)
    {
        server::pos_t y_diff = (current_round - initialRound) / 2 * ELEM_SIZE;
        if ((current_round - initialRound) % 2 == 0)
            y_diff *= -1;
        entityAction->newEntity = new WallElement(this->posX, this->posY + y_diff, getOwner());
    }
    return entityAction;
}

server::EntityInitialization *GreenPlayer::WallAttack::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    initialization->action.hp = DEFAULT_LIFE;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 0;
    initialization->sprite.sizeY = 0;
    initialization->sprite.path = "";
    this->initialRound = round;
    return initialization;
}

server::hp_t GreenPlayer::WallAttack::getDamage() {
    return 0;
}

server::Tribool GreenPlayer::WallAttack::collidesWith(const server::Entity &entity) {
    return server::Tribool::NA;
}


/*
 * ----------------------------------------------------------------------------------------------------------
 */

void GreenPlayer::WallAttack::WallElement::collide(const server::Entity &, server::round_t)
{
    modScore(getDamage());
    this->mustDestroy = true;
}

server::EntityAction *
GreenPlayer::WallAttack::WallElement::act(server::round_t, const server::Grid &vector) {
    server::EntityAction *action = new server::EntityAction;

    action->destroy = this->mustDestroy;
    action->speedX = 10;
    action->speedY = 0;
    return action;
}

server::EntityInitialization *GreenPlayer::WallAttack::WallElement::initialize(server::round_t round,
                                                                               const server::Grid &entity) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    initialization->action.hp = DEFAULT_LIFE;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 21;
    initialization->sprite.sizeY = 11;
    initialization->sprite.path = "media/sprites/crystalD.png";
    return initialization;
}

server::hp_t GreenPlayer::WallAttack::WallElement::getDamage() {
    return 3;
}

server::Tribool GreenPlayer::WallAttack::WallElement::collidesWith(const server::Entity &entity) {
    return entity.data.getTeam() != this->data->getTeam() ? server::T_TRUE : server::NA;
}

GreenPlayer::WallAttack::WallElement::WallElement(server::pos_t posX, server::pos_t posY, server::APlayer *owner)
        : Power(owner), mustDestroy(false), posX(posX), posY(posY)
{}

extern "C"
{
EXPORT_SYM server::ADynamicObject *getInstance() {
    return (new GreenPlayer());
}
}
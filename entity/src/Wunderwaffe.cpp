//
// Created by greg on 30/12/16.
//

#include <entities/Entity.hh>
#include <iostream>
#include "Wunderwaffe.hh"

void Wunderwaffe::collide(const server::Entity &entity, server::round_t) {
    this->damage += entity.obj->getDamage();
}

server::EntityAction *Wunderwaffe::act(server::round_t current_round, const server::Grid & environment) {
    server::EntityAction *action = new server::EntityAction();

    if (this->data->getHp() < 0) {
        action->destroy = true;
    }
    action->hp = this->data->getHp() - this->damage;
    this->damage = 0;

    if ((current_round % (20)) == 0) {
        BigBullet *bullet = new BigBullet(this->data->getPosX() + 280, this->data->getPosY());
        action->newEntity = bullet;
        return action;
    }

    if (current_round % (2 + (this->data->getHp() > DEFAULT_LIFE / 2)) == 0) {
        //TODO add bullet

    }
    return action;
}

server::EntityInitialization *
Wunderwaffe::initialize(server::round_t round, const server::Grid & environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization;
    this->damage = 0;
    this->startRound = round;
    initialization->sprite.path = "media/sprites/wunderwaffe1.png";
    initialization->sprite.sizeX = 860;
    initialization->sprite.sizeY = 270;
    initialization->team = server::Team::FOE;
    initialization->action.hp = DEFAULT_LIFE;
    initialization->action.speedX = 1;
    initialization->action.speedY = 0;

    return initialization;
}

server::hp_t Wunderwaffe::getDamage() {
    return DEFAULT_DAMAGE;
}

server::Tribool Wunderwaffe::collidesWith(const server::Entity &entity) {
    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::NA;
}

/*
 * ----------------------------------------------------------------------------------------
 */

Wunderwaffe::BigBullet::BigBullet(server::pos_t posX, server::pos_t posY) : posX(posX), posY(posY) {}

void Wunderwaffe::BigBullet::collide(const server::Entity &entity, server::round_t current_round) {
    this->mustDestroy = true;
}

server::EntityAction *Wunderwaffe::BigBullet::act(server::round_t current_round, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = this->mustDestroy;
    action->speedX = -5;
    action->speedY = -5;
    return action;
}

server::EntityInitialization *
Wunderwaffe::BigBullet::initialize(server::round_t round, const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    this->mustDestroy = false;
    initialization->sprite.path = "media/sprites/classicBulletGoingUpLeft.png";
    initialization->sprite.sizeX = 10;
    initialization->sprite.sizeY = 10;
    initialization->team = server::Team::FOE;
    initialization->action.hp = DEFAULT_LIFE;
    initialization->action.hp = 1;
    initialization->action.destroy = false;
    initialization->action.newEntity = nullptr;
    initialization->action.soundToPlay = "";
    initialization->action.speedX = -3;
    initialization->action.speedY = -3;
    initialization->posY = this->posY;
    initialization->posX = this->posX;
    return initialization;
}

server::hp_t Wunderwaffe::BigBullet::getDamage() {
    return DEFAULT_DAMAGE;
}

server::Tribool Wunderwaffe::BigBullet::collidesWith(const server::Entity &entity) {
    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::NA;
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new Wunderwaffe());
}
}

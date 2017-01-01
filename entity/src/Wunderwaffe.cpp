//
// Created by greg on 30/12/16.
//

#include <entities/Entity.hh>
#include <iostream>
#include <helpers/libloader/getDlLoader.hpp>
#include "Wunderwaffe.hh"

void Wunderwaffe::collide(const server::Entity &entity, server::round_t) {
    this->damage += entity.obj->getDamage();
}

server::EntityAction *Wunderwaffe::act(server::round_t current_round, const server::Grid & environment) {

    server::EntityAction *action = new server::EntityAction();

    action->hp = this->data->getHp();
    if (current_round - startRound < 350)
    {
        action->speedX = -2;
        if (current_round - startRound == 125)
        {
            auto hb = new Wunderwaffe::Hitbox();
            hb->setOwner(this, 1 * this->data->getSprite().sizeX);
            action->newEntity = hb;
        }
        if (current_round - startRound == 250)
        {
            auto hb = new Wunderwaffe::Hitbox();
            lastHitbox = hb;
            hb->setOwner(this, 2 * this->data->getSprite().sizeX);
            action->newEntity = hb;
        }
    }
    else
    {
        action->speedX = 0;
        if ((current_round - (startRound + 350)) / 500 % 2 == 0)
        {
            if (this->data->getPosX() > 2)
                action->speedX = -2;
        }
        else
        {
            if (this->data->getPosX() + 3 * this->data->getSprite().sizeX < FIELD_WIDTH - 2)
            {
                action->speedX = 2;
/*
                if (lastHitbox)
                {
                    server::pos_t whereIShouldBe = lastHitbox->data->getPosX() - this->data->getSprite().sizeX * 2;
                    action->speedX -= data->getPosX() - whereIShouldBe;
                }
*/
            }
        }


        if (this->data->getHp() < 0)
        {
            action->destroy = true;
        }

        action->hp = this->data->getHp() - this->damage;
        this->damage = 0;

        if (current_round % 10 == 0)
        {
            if ((current_round / 10 % 4) == 0)
            {
                BigBullet *bullet = new BigBullet(this->data->getPosX() + 280, this->data->getPosY());
                action->newEntity = bullet;
            }
            if ((current_round / 10 % 4) == 1)
            {
                BigBulletRight *bullet = new BigBulletRight(this->data->getPosX() + 610, this->data->getPosY() + 100);
                action->newEntity = bullet;
            }
            if ((current_round / 10 % 4) == 3)
            {
                BigBulletRight *bullet = new BigBulletRight(this->data->getPosX() + 560, this->data->getPosY() + 100);
                action->newEntity = bullet;
            }
            if ((current_round / 10 % 4) == 2)
            {
                BigBulletLeft *bullet = new BigBulletLeft(this->data->getPosX(), this->data->getPosY() + 30);
                action->newEntity = bullet;
            }
        }
        else if (current_round % 444 == 0)
        {
            action->newEntity = getDlLoader<server::ADynamicObject>("build/entity/Bomber")->getInstance();
        }
        else if (current_round % 222 == 0)
        {
            action->newEntity = getDlLoader<server::ADynamicObject>("build/entity/Ostwind")->getInstance();
        }
    }
    return action;
}

server::EntityInitialization *
Wunderwaffe::initialize(server::round_t round, const server::Grid & environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization;

    this->lastHitbox = nullptr;
    this->damage = 0;
    this->startRound = round;
    initialization->sprite.path = "media/sprites/wunderwaffe1.png";
    initialization->sprite.sizeX = 276;
    initialization->sprite.sizeY = 270;
    initialization->team = server::Team::FOE;
    initialization->action.hp = DEFAULT_LIFE;
    initialization->action.speedX = 1;
    initialization->action.speedY = 0;

    return initialization;
}

server::hp_t Wunderwaffe::getDamage() {
    return 0;
}

server::Tribool Wunderwaffe::collidesWith(const server::Entity &entity) {

    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::T_FALSE;
}

/*
 * ----------------------------------------------------------------------------------------
 */

Wunderwaffe::BigBullet::BigBullet(server::pos_t posX, server::pos_t posY) : posX(posX), posY(posY) {}

void Wunderwaffe::BigBullet::collide(const server::Entity &entity, server::round_t current_round) {
    this->mustDestroy = true;
}

server::EntityAction *Wunderwaffe::BigBullet::act(server::round_t, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = this->mustDestroy;
    action->speedX = -5;
    action->speedY = -5;
    return action;
}

server::EntityInitialization *
Wunderwaffe::BigBullet::initialize(server::round_t, const server::Grid &environment) {
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
    return 100;
}

server::Tribool Wunderwaffe::BigBullet::collidesWith(const server::Entity &entity) {
    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::T_FALSE;
}

Wunderwaffe::BigBullet::BigBullet()
{

}







extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new Wunderwaffe());
}
}

void Wunderwaffe::Hitbox::collide(const server::Entity &entity, server::round_t round)
{
    owner->collide(entity, round);
}

server::EntityAction *Wunderwaffe::Hitbox::act(server::round_t current_round, const server::Grid & environment) {

    auto action = owner->act(current_round, environment);

    if (action->newEntity)
    {
        delete action->newEntity;
        action->newEntity = nullptr;
    }

    auto whereIShouldBe = owner->data->getPosX() + x_offset;
    action->speedX -= data->getPosX() - whereIShouldBe;

    return action;
}

server::EntityInitialization *
Wunderwaffe::Hitbox::initialize(server::round_t round, const server::Grid & environment) {

    auto initialization = new server::EntityInitialization();

    initialization->sprite = owner->data->getSprite();
    initialization->sprite.path = "";
    initialization->posX = owner->data->getPosX() + x_offset;
    initialization->posY = owner->data->getPosY();
    initialization->action.speedX = owner->data->getVectX();
    initialization->action.speedY = owner->data->getVectY();
    initialization->team = owner->data->getTeam();

    return initialization;
}

server::hp_t Wunderwaffe::Hitbox::getDamage() {
    return owner->getDamage();
}

server::Tribool Wunderwaffe::Hitbox::collidesWith(const server::Entity &entity) {
    return owner->collidesWith(entity);
}

void Wunderwaffe::Hitbox::setOwner(server::ADynamicObject *owner, server::pos_t x_offset)
{
    this->owner = owner;
    this->x_offset = x_offset;
}





Wunderwaffe::BigBulletRight::BigBulletRight(server::pos_t posX, server::pos_t posY) : BigBullet(posX, posY)
{ }

server::EntityAction *Wunderwaffe::BigBulletRight::act(server::round_t current_round, const server::Grid &environment)
{
    auto act = BigBullet::act(current_round, environment);

    act->speedX = 3;
    act->speedY = -3;

    return (act);
}

server::EntityInitialization *
Wunderwaffe::BigBulletRight::initialize(server::round_t round, const server::Grid &environment)
{
    auto init = BigBullet::initialize(round, environment);

    init->sprite.path = "media/sprites/classicBulletGoingUpRight.png";

    return (init);
}

Wunderwaffe::BigBulletLeft::BigBulletLeft(server::pos_t posX, server::pos_t posY) : BigBullet(posX, posY)
{ }

server::EntityAction *Wunderwaffe::BigBulletLeft::act(server::round_t current_round, const server::Grid &environment)
{
    auto act = BigBullet::act(current_round, environment);

    act->speedX = -9;
    act->speedY = -3;

    return (act);
}

server::EntityInitialization *
Wunderwaffe::BigBulletLeft::initialize(server::round_t round, const server::Grid &environment)
{
    auto init = BigBullet::initialize(round, environment);

    init->sprite.path = "media/sprites/BigBulletWunderwaffe.png";

    return (init);
}

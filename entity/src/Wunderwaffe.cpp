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
    if (current_round - startRound < ROUNDS_MOVING)
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
        if ((current_round - (startRound + ROUNDS_MOVING)) / 500 % 2 == 0)
        {
            if (this->data->getPosX() > 2)
                action->speedX = -2;
        }
        else
        {
            if (this->data->getPosX() + this->data->getSprite().sizeX < FIELD_WIDTH - 2)
            {
                action->speedX = 2;
            }
        }


        if (this->data->getHp() < 0)
        {
            action->destroy = true;
        }

        action->hp = this->data->getHp() - this->damage;
        this->damage = 0;

        auto m = current_round % 30;
        if (m == 0 || m == 15) //top small cannon
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 300, this->data->getPosY() + 30, -5, -5, 9, 9,
                                              "media/sprites/classicBulletGoingUpLeft.png", 30);
            action->newEntity = bullet;
        }
        if (m == 1) //top medium cannon 1
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 330, this->data->getPosY(), -5, -5, 19, 19,
                                              "media/sprites/mediumBulletGoingUpLeft.png", 60);
            action->newEntity = bullet;
        }
        if (m == 2) //top medium cannon 2
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 340, this->data->getPosY(), -5, -5, 19, 19,
                                              "media/sprites/mediumBulletGoingUpLeft.png", 60);
            action->newEntity = bullet;
        }
        if (m == 3 || m == 18) //small cannon on the back 1
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 490, this->data->getPosY() + 110, -3, -3, 9, 9,
                                              "media/sprites/classicBulletGoingUpLeft.png", 30);
            action->newEntity = bullet;
        }
        if (m == 4) //small cannon on the back 2
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 555, this->data->getPosY() + 110, -3, -3, 9, 9,
                                              "media/sprites/classicBulletGoingUpLeft.png", 30);
            action->newEntity = bullet;
        }
        if (m == 5) //big cannon on the back
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 510, this->data->getPosY() + 65, -8, -4, 29, 25,
                                              "media/sprites/BigBulletWunderwaffeBack.png", 100);
            action->newEntity = bullet;
        }
        if (m == 6) //huge cannon
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 10, this->data->getPosY() + 30, -9, -3, 41, 30,
                                              "media/sprites/FieryBulletWunderwaffe.png", 200);
            action->newEntity = bullet;
        }
        if (m == 7) //medium-big cannon in front
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 30, this->data->getPosY() + 120, -9, -2, 38, 14,
                                              "media/sprites/BigBulletWunderwaffeFront.png", 100);
            action->newEntity = bullet;
        }
        if (m == 8 || m == 23) //small cannon in front
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 80, this->data->getPosY() + 185, -9, 0, 12, 4,
                                              "media/sprites/classicBullet.png", 30);
            action->newEntity = bullet;
        }
        if (m == 9) //small cannon behind next to the big one
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 610, this->data->getPosY() + 80, -4, -2, 9, 9,
                                              "media/sprites/classicBulletGoingUpLeft.png", 30);
            action->newEntity = bullet;
        }
        if (m == 10 || m == 25) //small cannon behind
        {
            BigBullet *bullet = new BigBullet(this->data->getPosX() + 715, this->data->getPosY() + 80, 3, -3, 9, 9,
                                              "media/sprites/classicBulletGoingUpRight.png", 30);
            action->newEntity = bullet;
        }


/*
        if (current_round % 1000 == 0)
        {
            action->newEntity = getDlLoader<server::ADynamicObject>("build/entity/Bomber")->getInstance();
        }
        else if (current_round % 500 == 0)
        {
            action->newEntity = getDlLoader<server::ADynamicObject>("build/entity/Ostwind")->getInstance();
        }
*/
    }
    return action;
}

server::EntityInitialization *
Wunderwaffe::initialize(server::round_t round, const server::Grid & environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization;

    this->lastHitbox = nullptr;
    this->damage = 0;
    this->startRound = round;
    initialization->sprite.path = "media/sprites/wunderwaffe1v2.png";
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

Wunderwaffe::BigBullet::BigBullet(server::pos_t posX, server::pos_t posY, server::speed_t speedX, server::speed_t speedY, int sizeX,
                                  int sizeY, const std::string &sprite, server::hp_t damage) :
        posX(posX), posY(posY), speedX(speedX), speedY(speedY), sizeX(sizeX), sizeY(sizeY), sprite(sprite), damage(damage)
{}

void Wunderwaffe::BigBullet::collide(const server::Entity &entity, server::round_t current_round) {
    this->mustDestroy = true;
}

server::EntityAction *Wunderwaffe::BigBullet::act(server::round_t, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = this->mustDestroy;
    action->speedX = speedX;
    action->speedY = speedY;
    return action;
}

server::EntityInitialization *
Wunderwaffe::BigBullet::initialize(server::round_t, const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    this->mustDestroy = false;
    initialization->sprite.path = sprite;
    initialization->sprite.sizeX = sizeX;
    initialization->sprite.sizeY = sizeY;
    initialization->team = server::Team::FOE;
    initialization->action.hp = DEFAULT_LIFE;
    initialization->action.hp = 1;
    initialization->action.destroy = false;
    initialization->action.newEntity = nullptr;
    initialization->action.soundToPlay = "";
    initialization->action.speedX = speedX;
    initialization->action.speedY = speedY;
    initialization->posY = this->posY;
    initialization->posX = this->posX;
    return initialization;
}

server::hp_t Wunderwaffe::BigBullet::getDamage() {
    return damage;
}

server::Tribool Wunderwaffe::BigBullet::collidesWith(const server::Entity &entity) {
    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::T_FALSE;
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

//
// Created by greg on 30/12/16.
//

#include <entities/Entity.hh>
#include <iostream>
#include <entities/VisualFx.hh>
#include "Ostwind.hh"

void Ostwind::collide(const server::Entity &entity, server::round_t) {
    this->damage += entity.obj->getDamage();
}

server::EntityAction *Ostwind::act(server::round_t current_round, const server::Grid & environment) {
    server::EntityAction *action = new server::EntityAction();

    if (this->data->getHp() < 0)
    {
        action->destroy = true;
        action->newEntity = new server::VisualFx(data->getPosX() + 30, data->getPosY() + server::VisualFx::Y_EXPLOSION_A, "media/sprites/explosionA.png", "media/sounds/explosion1.ogg", 100);
    }
    else
    {
        action->hp = this->data->getHp() - this->damage;
        this->damage = 0;

        if ((current_round % (30)) == 0)
        {
            OstwindBullet *bullet = new OstwindBullet(this->data->getPosX() + 10, this->data->getPosY());
            action->newEntity = bullet;
            return action;
        }

        action->speedX = -2;
    }

    return action;
}

server::EntityInitialization *
Ostwind::initialize(server::round_t round, const server::Grid & environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization;
    this->damage = 0;
    this->startRound = round;
    initialization->sprite.path = "media/sprites/wirbelwind.png";
    initialization->sprite.sizeX = 128;
    initialization->sprite.sizeY = 68;
    initialization->posY = FIELD_HEIGHT - initialization->sprite.sizeY - 100;
    initialization->posX = FIELD_WIDTH;
    initialization->team = server::Team::FOE;
    initialization->action.hp = DEFAULT_LIFE;
    initialization->action.speedX = 0;
    initialization->action.speedY = 0;

    return initialization;
}

server::hp_t Ostwind::getDamage() {
    return 0;
}

server::Tribool Ostwind::collidesWith(const server::Entity &entity) {
    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::T_FALSE;
}

/*
 * ----------------------------------------------------------------------------------------
 */

Ostwind::OstwindBullet::OstwindBullet(server::pos_t posX, server::pos_t posY) : posX(posX), posY(posY) {}

void Ostwind::OstwindBullet::collide(const server::Entity &entity, server::round_t current_round) {
    this->mustDestroy = true;
}

server::EntityAction *Ostwind::OstwindBullet::act(server::round_t, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = this->mustDestroy;
    action->speedX = -5;
    action->speedY = -5;
    return action;
}

server::EntityInitialization *
Ostwind::OstwindBullet::initialize(server::round_t, const server::Grid &environment) {
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

server::hp_t Ostwind::OstwindBullet::getDamage() {
    return DEFAULT_DAMAGE;
}

server::Tribool Ostwind::OstwindBullet::collidesWith(const server::Entity &entity) {
    return entity.obj->data->getTeam() == server::Team::PLAYER ? server::T_TRUE : server::T_FALSE;
}

extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new Ostwind());
}
}

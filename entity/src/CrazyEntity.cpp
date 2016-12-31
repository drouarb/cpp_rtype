//
// Created by greg on 30/12/16.
//

#include <entities/Entity.hh>
#include "CrazyEntity.hh"

using namespace server;


CrazyEntity::CrazyEntity() : lostHp(0), mustDestroy(false) {}

void CrazyEntity::collide(const server::Entity &entity, server::round_t current_round) {
    lostHp += entity.obj->getDamage();
    if (this->data->getHp() - lostHp <= 0) {
        mustDestroy = true;
    }
}

server::EntityInitialization *CrazyEntity::initialize(server::round_t round, const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = DEFAULT_HP;
    initialization->team = server::Team::FOE;
    initialization->action.speedX = -3;
    initialization->action.speedY = 0;
    initialization->sprite.sizeX = 350;
    initialization->sprite.sizeY = 100;
    initialization->sprite.path = "media/sprites/ju87.png";
    this->startingRound = round;

    return initialization;
}

server::EntityAction *CrazyEntity::act(server::round_t current_round, const server::Grid &) {
    server::EntityAction *a;
    a = new server::EntityAction();
    a->destroy = mustDestroy;
    a->speedX = -3;
    a->speedY = 0;
    a->hp = this->data->getHp() - lostHp;
    lostHp = 0;

    if (this->data->getPosX() < FIELD_BORDER_RIGHT - 50)
    {
        if (current_round % 6 == 0)
        {
            a->newEntity = new CrazyProjectile(this->data->getPosX() - 10,
                                               this->data->getPosY() + current_round % 24 * 3 + 10);
        }
    }
    return (a);
}

server::hp_t CrazyEntity::getDamage() {
    return (32000);
}

server::Tribool CrazyEntity::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}

/*
 * ----------------------------------------------
 */

void CrazyEntity::CrazyProjectile::collide(const server::Entity &entity, server::round_t current_round) {
    if (entity.data.getTeam() == server::Team::FOE) {
        return;
    }
    this->isCollide = current_round;
}

server::EntityAction *CrazyEntity::CrazyProjectile::act(server::round_t current_round, const server::Grid &) {
    server::EntityAction *a = new server::EntityAction();
    if (this->isCollide) {
        a->destroy = true;
        a->soundToPlay = ""; //TODO add EXPLOSSSSSSSSSSSSSSSSSIONNN BOUM BAM BIM BROUM
        return (a);
    }
    a->speedX = -12;
    return (a);
}

server::EntityInitialization *CrazyEntity::CrazyProjectile::initialize(server::round_t,
                                                                       const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization(""); //TODO Add sprite
    initialization->action.speedX = -3;
    initialization->action.speedY = 0;
    initialization->team = server::Team::FOE;
    initialization->sprite.sizeX = 20;
    initialization->sprite.sizeY = 20;
    initialization->posX = this->posX;
    initialization->posY = this->posY - initialization->sprite.sizeY / 2;
    initialization->sprite.path = "media/sprites/magicBullet.png";
    return initialization;
}

server::hp_t CrazyEntity::CrazyProjectile::getDamage() {
    return DAMMAGE;
}

CrazyEntity::CrazyProjectile::CrazyProjectile(server::speed_t posX, server::speed_t posY)
        : isCollide(0) {
    this->posX = posX;
    this->posY = posY;
}

server::Tribool CrazyEntity::CrazyProjectile::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}


extern "C"
{
server::ADynamicObject *getInstance() {
    return (new CrazyEntity());
}
}

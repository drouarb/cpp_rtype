//
// Created by greg on 15/12/2016.
//

#define LOG_INFO

#include "definitions.hh"
#include <BasicNastyEntity.hh>
#include <iostream>

BasicNastyEntity::BasicNastyEntity() : notifyCollision(nullptr), stopwatch(IStopwatch::getInstance()) {
    this->stopwatch->set();
}

void BasicNastyEntity::collide(const server::Entity &entity) {
    this->notifyCollision = new server::EntityAction();
    this->notifyCollision->hp = this->data->getHp() - entity.obj->getDamage();
    std::cout << "COLIIIIIIIIIIIIIIIIIIIIIIIIIDE with: " << entity.data.getId() << std::endl;
    INFO("I'm the vilain nasty player : COLLIDE")
    if (this->notifyCollision->hp <= 0) {
        this->notifyCollision->destroy = true;
        INFO("I'm the vilain nasty player : I'm ded WWZKKZZOWZKWZO")
    }
}

server::EntityAction *BasicNastyEntity::act(server::round_t current_round)
{
    INFO("Next action NastyEntity (hp: " << this->data->getHp() << ", id: " << this->data->getId() << ")")
    server::EntityAction * a;
    if (this->notifyCollision) {
        a = this->notifyCollision;
        this->notifyCollision = nullptr;
    } else {
        a = new server::EntityAction();
        a->destroy = false;
        a->speedX = 0;
        a->hp = this->data->getHp();
    }

    if (this->stopwatch->ellapsedMs() > FIRE_FREQUENCY) {
        INFO("I'm the vilain nasty player : BOUM BIM BAM")
        this->stopwatch->set();
        VeryNastyProjectile *projectile = new VeryNastyProjectile(this->data->getPosX() - 3, this->data->getPosY());
        a->newEntity = projectile;
    }
    INFO("Next action OK")
    return (a);
}

server::EntityInitialization *BasicNastyEntity::initialize() {
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = DEFAULT_HP;
    initialization->team = server::Team::FOE;
    initialization->action.speedX = 1;
    initialization->action.speedY = 0;
    initialization->sprite.sizeX = 100;
    initialization->sprite.sizeY = 100;
    initialization->sprite.path = "media/references/ALL_GONE.jpg";

    INFO("I'm the vilain nasty player: ");
    return initialization;//TODO Add sprite
}

server::hp_t BasicNastyEntity::getDamage() {
    return NASTY_COLLISION_DAMAGE;
}

bool BasicNastyEntity::collideWith(const server::Entity &entity) {
    return this->data->getTeam() != entity.data.getTeam();
}

void BasicNastyEntity::VeryNastyProjectile::collide(const server::Entity &entity) {
    if (entity.data.getTeam() == server::Team::FOE) {
        return;
    }
    this->isCollide = true;
}

server::EntityAction *BasicNastyEntity::VeryNastyProjectile::act(server::round_t current_round)
{
    server::EntityAction * a = new server::EntityAction();
    if (this->isCollide) {
        a->destroy = true;
        a->soundToPlay = ""; //TODO add EXPLOSSSSSSSSSSSSSSSSSIONNN BOUM BAM BIM BROUM
        return (a);
    }
    a->speedX = -20;
    return (a);
}

server::EntityInitialization *BasicNastyEntity::VeryNastyProjectile::initialize() {
    server::EntityInitialization *initialization = new server::EntityInitialization(""); //TODO Add sprite
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->action.speedX = -3;
    initialization->action.speedY = 0;
    initialization->team = server::Team::FOE;
    initialization->sprite.sizeX = 40;
    initialization->sprite.sizeY = 40;
    initialization->sprite.path = "media/references/bf_110_br_schrodyus-d5u1r3c.gif";
    return initialization;
}

server::hp_t BasicNastyEntity::VeryNastyProjectile::getDamage() {
    return NASTY_DAMAGE;
}

BasicNastyEntity::VeryNastyProjectile::VeryNastyProjectile(server::speed_t posX, server::speed_t posY)
        : isCollide(false) {
    this->posX = posX;
    this->posY = posY;
}

bool BasicNastyEntity::VeryNastyProjectile::collideWith(const server::Entity &entity) {
    return this->data->getTeam() != entity.data.getTeam();
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new BasicNastyEntity());
}
}

//
// Created by greg on 15/12/2016.
//

#define LOG_INFO

#include "Definitions.hh"
#include <BasicNastyEntity.hh>
#include <iostream>
#include <vector>

BasicNastyEntity::BasicNastyEntity() : lostHp(0), mustDestroy(false)
{ }

void BasicNastyEntity::collide(const server::Entity &entity, server::round_t current_round) {

    INFO("COLIIIIIIIIIIIIIIIIIIIIIIIIIDE with: " << entity.data.getId() << ", at round:" << current_round);
    INFO("I'm the vilain nasty player : COLLIDE")
    lostHp += entity.obj->getDamage();
    if (this->data->getHp() - lostHp <= 0) {
        mustDestroy = true;
        INFO("I'm the vilain nasty player : I'm ded WWZKKZZOWZKWZO")
    }
}

server::EntityAction *BasicNastyEntity::act(server::round_t current_round, const std::vector<server::Entity *> &)
{
    INFO("Next action NastyEntity (hp: " << this->data->getHp() << ", id: " << this->data->getId() << ", round:" << current_round << ")")
    server::EntityAction * a;
    a = new server::EntityAction();
    a->destroy = mustDestroy;
    a->speedX = 0;
    a->speedY = 0;
    a->hp = this->data->getHp() - lostHp;
    lostHp = 0;

    if (current_round - startingRound < ROUNDS_MOVING)
    {
        a->speedX = -SPEED;
    }
    else
    {
        if (current_round % (6 * FIRE_FREQUENCY) == 0)
        {
            INFO("I'm the vilain nasty player : BOUM BIM BAM")
            VeryNastyProjectile *projectile = new VeryNastyProjectile(this->data->getPosX() - 3,
                                                                      this->data->getPosY() + this->data->getSprite().sizeY / 2);
            a->newEntity = projectile;
        }
    }
    INFO("Next action OK")
    return (a);
}

server::EntityInitialization *BasicNastyEntity::initialize(server::round_t round, const std::vector<server::Entity *> &)
{
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = DEFAULT_HP;
    initialization->team = server::Team::FOE;
    initialization->action.speedX = 0;
    initialization->action.speedY = 0;
    initialization->sprite.sizeX = 120;
    initialization->sprite.sizeY = 120;
    initialization->sprite.path = "media/references/ALL_GONE.jpg";
    this->startingRound = round;

    INFO("I'm the vilain nasty player: ");
    return initialization;
}

server::hp_t BasicNastyEntity::getDamage() {
    return 0;
}

server::Tribool BasicNastyEntity::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}

void BasicNastyEntity::VeryNastyProjectile::collide(const server::Entity &entity, server::round_t current_round) {
    INFO("TEST COLLISION")
    if (entity.data.getTeam() == server::Team::FOE) {
        return;
    }
    INFO("MISSILE COLLIDE EXPLOSION (entity=" << entity.data.getId() << " me=" << data->getId() << " round : " << current_round << ")");
    this->isCollide = current_round;
}

server::EntityAction *BasicNastyEntity::VeryNastyProjectile::act(server::round_t current_round, const std::vector<server::Entity *> &)
{
    server::EntityAction * a = new server::EntityAction();
    if (this->isCollide) {
        a->destroy = true;
        a->soundToPlay = ""; //TODO add EXPLOSSSSSSSSSSSSSSSSSIONNN BOUM BAM BIM BROUM
        return (a);
    }
    a->speedX = -3;
    return (a);
}

server::EntityInitialization *BasicNastyEntity::VeryNastyProjectile::initialize(server::round_t, const std::vector<server::Entity *> &)
{
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

server::hp_t BasicNastyEntity::VeryNastyProjectile::getDamage() {
    return NASTY_DAMAGE;
}

BasicNastyEntity::VeryNastyProjectile::VeryNastyProjectile(server::speed_t posX, server::speed_t posY)
        : isCollide(0) {
    this->posX = posX;
    this->posY = posY;
}

server::Tribool BasicNastyEntity::VeryNastyProjectile::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new BasicNastyEntity());
}
}

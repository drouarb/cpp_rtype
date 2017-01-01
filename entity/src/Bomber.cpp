//
// Created by greg on 15/12/2016.
//


#include "Definitions.hh"
#include "../../server/include/Grid.hh"
#include <Bomber.hh>
#include <entities/VisualFx.hh>
#include <iostream>

Bomber::Bomber() : lostHp(0), mustDestroy(false)
{ }

void Bomber::collide(const server::Entity &entity, server::round_t current_round) {

    lostHp += entity.obj->getDamage();
    if (this->data->getHp() - lostHp <= 0) {
        mustDestroy = true;
    }
}

server::EntityInitialization *Bomber::initialize(server::round_t round, const server::Grid &environment)
{
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = DEFAULT_HP;
    initialization->team = server::Team::FOE;
    initialization->action.speedX = 0;
    initialization->action.speedY = 0;
    initialization->sprite.sizeX = 350;
    initialization->sprite.sizeY = 110;
    initialization->posY = 100;
    initialization->posX = FIELD_WIDTH;
    initialization->sprite.path = "media/sprites/he111.png";
    this->startingRound = round;

    return initialization;
}

server::EntityAction *Bomber::act(server::round_t current_round, const server::Grid &)
{
    server::EntityAction * a;
    a = new server::EntityAction();
    a->destroy = mustDestroy;
    a->speedX = -2;
    a->speedY = 0;
    a->hp = this->data->getHp() - lostHp;
    lostHp = 0;

    if (mustDestroy)
    {
        a->newEntity = new server::VisualFx(data->getPosX() + 30, data->getPosY() + server::VisualFx::Y_EXPLOSION_A,
                                            "media/sprites/explosionA.png", "media/sounds/explosion3.ogg", 100,
                                            0, server::VisualFx::Y_EXPLOSION_A);
        return (a);
    }

    if (current_round - startingRound >= 100)
    {
        if (current_round % 60 == 0)
        {
            BomberProjectile *projectile = new BomberProjectile(this->data->getPosX() + 100,
                                                                this->data->getPosY() + 100);
            a->newEntity = projectile;
        }
    }
    return (a);
}

server::hp_t Bomber::getDamage() {
    return (32000);
}

server::Tribool Bomber::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}

void Bomber::BomberProjectile::collide(const server::Entity &entity, server::round_t current_round) {
    if (entity.data.getTeam() == server::Team::FOE) {
        return;
    }
    this->collides = true;
}

server::EntityAction *Bomber::BomberProjectile::act(server::round_t current_round, const server::Grid &)
{
    server::EntityAction * a = new server::EntityAction();
    if (this->collides) {
        a->destroy = true;
        a->soundToPlay = ""; //TODO add EXPLOSSSSSSSSSSSSSSSSSIONNN BOUM BAM BIM BROUM
        return (a);
    }
    a->speedX = -1;
    a->speedY = 5;
    return (a);
}

server::EntityInitialization *Bomber::BomberProjectile::initialize(server::round_t,
                                                                                const server::Grid &environment)
{
    server::EntityInitialization *initialization = new server::EntityInitialization(""); //TODO Add sprite
    initialization->action.speedX = -3;
    initialization->action.speedY = 0;
    initialization->team = server::Team::FOE;
    initialization->sprite.sizeX = 20;
    initialization->sprite.sizeY = 20;
    initialization->posX = this->posX;
    initialization->posY = this->posY - initialization->sprite.sizeY / 2;
    initialization->sprite.path = "media/sprites/missileA_b_right.png";
    return initialization;
}

server::hp_t Bomber::BomberProjectile::getDamage() {
    return 50;
}

Bomber::BomberProjectile::BomberProjectile(server::speed_t posX, server::speed_t posY)
        : collides(false) {
    this->posX = posX;
    this->posY = posY;
}

server::Tribool Bomber::BomberProjectile::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}

extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new Bomber());
}
}

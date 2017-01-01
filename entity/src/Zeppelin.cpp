//
// Created by greg on 15/12/2016.
//


#define _USE_MATH_DEFINES
#include <cmath>
#include "Definitions.hh"
#include "../../server/include/Grid.hh"
#include <Zeppelin.hh>

Zeppelin::Zeppelin() : lostHp(0), mustDestroy(false)
{ }

server::EntityInitialization *Zeppelin::initialize(server::round_t round, const server::Grid &environment)
{
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = 2000;
    initialization->team = server::Team::FOE;
    initialization->action.speedX = 0;
    initialization->action.speedY = 0;
    initialization->sprite.sizeX = 277;
    initialization->sprite.sizeY = 241;
    initialization->sprite.path = "media/sprites/zeppelin.png";
    this->startRound = round;

    return initialization;
}

void Zeppelin::collide(const server::Entity &entity, server::round_t current_round)
{
    lostHp += entity.obj->getDamage();
    if (this->data->getHp() - lostHp <= 0)
    {
        mustDestroy = true;
    }
}

server::EntityAction *Zeppelin::act(server::round_t current_round, const server::Grid &)
{
    server::EntityAction * action;
    action = new server::EntityAction();
    action->destroy = mustDestroy;
    action->hp = this->data->getHp() - lostHp;
    lostHp = 0;

    if (current_round - startRound < 400)
    {
        action->speedX = -3;
        if (current_round - startRound == 100)
        {
            auto hb = new Zeppelin::Hitbox();
            hb->setOwner(this, 1 * this->data->getSprite().sizeX);
            action->newEntity = hb;
        }
        if (current_round - startRound == 200)
        {
            auto hb = new Zeppelin::Hitbox();
            hb->setOwner(this, 2 * this->data->getSprite().sizeX);
            action->newEntity = hb;
        }
    }
    else
    {
        if (current_round % density == 0)
        {
            action->newEntity = new NovaMissile(this->data->getPosX() + this->data->getSprite().sizeX * 3 / 2 + 80,
                                                this->data->getPosY() + this->data->getSprite().sizeY / 2 + 50,
                                                0, static_cast<double>(current_round / density % 78) * 0.04);
        }
        else if (current_round % density == 1)
        {
            action->newEntity = new NovaMissile(this->data->getPosX() + this->data->getSprite().sizeX * 3 / 2 - 140,
                                                this->data->getPosY() + this->data->getSprite().sizeY / 2 + 50,
                                                0, M_PI - static_cast<double>(current_round / density % 78) * 0.04);
        }
    }

    return (action);
}

server::hp_t Zeppelin::getDamage()
{
    if (this->data->getVectX() != 0)
        return (10);
    return (0);
}

server::Tribool Zeppelin::collidesWith(const server::Entity &entity)
{
/*
    if (this->data->getVectX() != 0)
        return (server::NA);
*/
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}





void Zeppelin::Hitbox::collide(const server::Entity &entity, server::round_t round)
{
    owner->collide(entity, round);
}

server::EntityAction *Zeppelin::Hitbox::act(server::round_t current_round, const server::Grid & environment) {

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
Zeppelin::Hitbox::initialize(server::round_t round, const server::Grid & environment) {

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

server::hp_t Zeppelin::Hitbox::getDamage() {
    return owner->getDamage();
}

server::Tribool Zeppelin::Hitbox::collidesWith(const server::Entity &entity) {
    return owner->collidesWith(entity);
}

void Zeppelin::Hitbox::setOwner(server::ADynamicObject *owner, server::pos_t x_offset)
{
    this->owner = owner;
    this->x_offset = x_offset;
}






Zeppelin::NovaMissile::NovaMissile(server::pos_t posX, server::pos_t posY, int nb, double angle) :
        posX(posX), posY(posY), nb(nb)
{
    this->angle = angle + startingAngle[nb];
}

server::EntityInitialization *Zeppelin::NovaMissile::initialize(server::round_t round, const server::Grid &environment) {

    startRound = round;
    this->mustDestroy = false;
    server::EntityInitialization *initialization = new server::EntityInitialization;
    initialization->posY = this->posY;
    initialization->posX = this->posX;
    initialization->sprite = std::string("media/sprites/magicBullet.png");
    initialization->action.speedX = static_cast<server::speed_t >(cos(angle) * speed);
    initialization->action.speedY = static_cast<server::speed_t >(sin(angle) * speed);
    initialization->team = server::Team::FOE;
    initialization->sprite.sizeX = 24;
    initialization->sprite.sizeY = 24;
    return initialization;
}

void Zeppelin::NovaMissile::collide(const server::Entity &entity, server::round_t)
{
    this->mustDestroy = true;
}

server::EntityAction *Zeppelin::NovaMissile::act(server::round_t current_round, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    if (nb < 7 && current_round == startRound)
    {
        action->newEntity = new NovaMissile(data->getPosX(), data->getPosY(), nb + 1, angle);
    }
    action->speedX = data->getVectX();
    action->speedY = data->getVectY();

    action->destroy = this->mustDestroy;
    return action;
}

server::hp_t Zeppelin::NovaMissile::getDamage() {
    return 40;
}

server::Tribool Zeppelin::NovaMissile::collidesWith(const server::Entity &entity) {
    return (entity.data.getTeam() == server::FOE ? server::T_FALSE : server::T_TRUE);
}

const double Zeppelin::NovaMissile::startingAngle[8] =
        {
                0 * (M_PI / 4),
                1 * (M_PI / 4),
                2 * (M_PI / 4),
                3 * (M_PI / 4),
                4 * (M_PI / 4),
                5 * (M_PI / 4),
                6 * (M_PI / 4),
                7 * (M_PI / 4)
        };






extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new Zeppelin());
}
}

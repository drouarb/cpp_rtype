//
// Created by greg on 22/12/16.
//

#include <entities/Entity.hh>
#include <iostream>
#include "YellowPlayer.hh"
#include "math.h"

server::EntityInitialization *YellowPlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlB.png";
    return pInitialization;
}

server::ADynamicObject *YellowPlayer::createAttack(server::attackId_t id, server::round_t round) {
    if (id == 1)
    {
        setAttackWait(id, 15, round);
        return new NovaMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                                this->data->getPosY() + 10, 0);
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                                this->data->getPosY() + 10,
                                "media/sprites/daggerC.png");
    }
}






YellowPlayer::NovaMissile::NovaMissile(server::APlayer * owner, server::pos_t posX, server::pos_t posY, int nb) :
        Power(owner), posX(posX), posY(posY), nb(nb)
{ }

server::EntityInitialization *YellowPlayer::NovaMissile::initialize(server::round_t round, const server::Grid &environment) {

    startRound = round;
    this->mustDestroy = false;
    server::EntityInitialization *initialization = new server::EntityInitialization;
    initialization->posY = this->posY;
    initialization->posX = this->posX;
    initialization->sprite = std::string("media/sprites/crystalC.png");
    initialization->action.speedX = 0;
    initialization->action.speedY = 0;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 24;
    initialization->sprite.sizeY = 24;
    return initialization;
}

void YellowPlayer::NovaMissile::collide(const server::Entity &entity, server::round_t)
{
    if (entity.data.getTeam() == server::FOE)
    {
        modScore(static_cast<server::score_t >(getDamage()));
    }
    this->mustDestroy = true;
}

server::EntityAction *YellowPlayer::NovaMissile::act(server::round_t current_round, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    if (nb < 7 && current_round == startRound)
    {
        action->newEntity = new NovaMissile(getOwner(), data->getPosX(), data->getPosY(), nb + 1);
    }
    else
    {
        int circle_time = 78;
        if (current_round - startRound >= circle_time)
        {
            action->speedX = data->getVectX();
            action->speedY = data->getVectY();
        }
        else
        {
            auto circle_speed = 10;
            auto rad = ((current_round - startRound) % circle_time) * 0.04 + startingAngle[nb];
            auto vectX = cos(rad) * circle_speed;
            auto vectY = sin(rad) * circle_speed;
            action->speedX = static_cast<server::speed_t >(vectX);
            action->speedY = static_cast<server::speed_t >(vectY);
        }
    }

    action->destroy = this->mustDestroy;
    return action;
}

server::hp_t YellowPlayer::NovaMissile::getDamage() {
    return 10;
}

server::Tribool YellowPlayer::NovaMissile::collidesWith(const server::Entity &entity) {
    return (entity.data.getTeam() == server::PLAYER ? server::T_FALSE : server::T_TRUE);
}

const double YellowPlayer::NovaMissile::startingAngle[8] =
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
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new YellowPlayer());
}
}

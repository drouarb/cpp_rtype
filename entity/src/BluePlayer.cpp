//
// Created by greg on 22/12/16.
//

#include <iostream>
#include <entities/Entity.hh>
#include "BluePlayer.hh"

server::EntityInitialization *BluePlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlC.png";
    return pInitialization;
}

server::ADynamicObject *BluePlayer::createAttack(server::attackId_t id, server::round_t round) {
    if (id == 1)
    {
        setAttackWait(id, 3, round);
        return new MagicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX + BULLET_SIZE + 1,
                                this->data->getPosY(),
                                round, "media/sprites/crystalB.png");
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                                this->data->getPosY() + 10,
                                "media/sprites/daggerB.png");
    }
}




using namespace server;

BluePlayer::MagicMissile::MagicMissile(APlayer *owner, pos_t posX, pos_t posY, round_t startRound, const std::string & sprite)
        : Power(owner), mustDestroy(false), posX(posX), posY(posY), sprite(sprite)
{ }


void BluePlayer::MagicMissile::collide(const Entity &entity, server::round_t current_round) {
    INFO("MagicMissile collide with : " << entity.data.getId() << "(id: " << this->data->getId() << ")")
    if (entity.data.getTeam() == FOE)
    {
        modScore(static_cast<score_t >(getDamage()));
    }
    this->mustDestroy = true;
}

EntityAction *BluePlayer::MagicMissile::act(round_t current_round, const server::Grid &)
{
    server::EntityAction *entityAction = new server::EntityAction();

    if (this->mustDestroy) {
        entityAction->destroy = true;
        INFO("MagicMassile ded" << this->data->getId() << ", x:" << this->data->getPosX() << ", y: "
                                << this->data->getPosY())
    }
    auto circle_speed = 15;
    auto x_speed = 5;
    auto rad = ((current_round - startRound) % 15) * 0.4;
    auto vectX = cos(rad) * circle_speed + x_speed;
    auto vectY = sin(rad) * circle_speed;
    entityAction->speedX = static_cast<speed_t >(vectX);
    entityAction->speedY = static_cast<speed_t >(vectY);

/*
    entityAction->speedX = 5;
    entityAction->speedY = 0;
*/

    return entityAction;
}

EntityInitialization *BluePlayer::MagicMissile::initialize(round_t round, const Grid &environment)
{
    EntityInitialization *initialization = new EntityInitialization();
    initialization->action.hp = -1;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = BULLET_SIZE;
    initialization->sprite.sizeY = BULLET_SIZE;
    initialization->sprite.path = sprite;
    this->startRound = round;
    return initialization;
}

hp_t BluePlayer::MagicMissile::getDamage() {
    return 8;
}

Tribool BluePlayer::MagicMissile::collidesWith(const Entity &entity) {
    return (entity.data.getTeam() != server::Team::PLAYER ? T_TRUE : T_FALSE);
}





extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new BluePlayer());
}
}

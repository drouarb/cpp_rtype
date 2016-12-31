//
// Created by greg on 22/12/16.
//

#include <iostream>
#include <entities/Entity.hh>
#include "GreenPlayer.hh"

server::EntityInitialization *GreenPlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlD.png";
    return pInitialization;
}

server::ADynamicObject *GreenPlayer::createAttack(server::attackId_t id, server::round_t round)
{
//    setAttackWait(id, 50, round);
    setAttackWait(id, 10, round);
//    return new BasicMissile(this->data->getPosX() + this->data->getSprite().sizeX,
//                            this->data->getPosY() + this->data->getSprite().sizeY, "media/sprites/missileD.png");
    return new WallAttack(this, this->data->getPosX() + this->data->getSprite().sizeX,
                          this->data->getPosY() + this->data->getSprite().sizeY);
}

/*
 * ----------------------------------------------------------------------------------------------------------
 */

GreenPlayer::WallAttack::WallAttack(server::APlayer *owner, server::pos_t posX, server::pos_t posY)
        : Power(owner), posX(posX), posY(posY), initialRound(0),
          layerLeft(6), nextPlace(TOP) {}

void GreenPlayer::WallAttack::collide(const server::Entity &entity, server::round_t current_round) {}

server::EntityAction *
GreenPlayer::WallAttack::act(server::round_t current_round, const server::Grid &vector) {
    server::EntityAction *entityAction = new server::EntityAction();
    if (!this->initialRound) {
        this->initialRound = current_round;
    }
    entityAction->hp = this->data->getHp();
    entityAction->speedX = 3;
    entityAction->speedY = 0;
    if (this->layerLeft == 0) {
        entityAction->destroy = true;
        return entityAction;
    }
    if (nextPlace == DOWN) {
        nextPlace = TOP;
        entityAction->newEntity = new WallElement(this->posX - (21 * layerLeft) + 50,
                                                  this->posY - (11 * layerLeft), getOwner());
//        std::cout << "Round " << current_round << ", element at " << this->posX - 34 << ", " << this->posY - 34 << std::endl;
        this->layerLeft--;
    } else {
        nextPlace = DOWN;
        entityAction->newEntity = new WallElement(this->posX - (21 * layerLeft) + 50,
                                                  this->posY + (11 * layerLeft), getOwner());
//        std::cout << "Round " << current_round << ", element at " << this->posX - 34 << ", " << this->posY + 34 << std::endl;
    }
    return entityAction;
}

server::EntityInitialization *GreenPlayer::WallAttack::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    initialization->action.hp = DEFAULT_LIFE;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 0;
    initialization->sprite.sizeY = 0;
    initialization->sprite.path = "";
    return initialization;
}

server::hp_t GreenPlayer::WallAttack::getDamage() {
    return DAMMAGE;
}

server::Tribool GreenPlayer::WallAttack::collidesWith(const server::Entity &entity) {
    return server::Tribool::NA;
}


/*
 * ----------------------------------------------------------------------------------------------------------
 */

void GreenPlayer::WallAttack::WallElement::collide(const server::Entity &, server::round_t)
{
    modScore(getDamage());
    this->mustDestroy = true;
}

server::EntityAction *
GreenPlayer::WallAttack::WallElement::act(server::round_t, const server::Grid &vector) {
    server::EntityAction *action = new server::EntityAction;

    action->destroy = this->mustDestroy;
    action->speedX = 10;
    action->speedY = 0;
    return action;
}

server::EntityInitialization *GreenPlayer::WallAttack::WallElement::initialize(server::round_t round,
                                                                               const server::Grid &entity) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    initialization->action.hp = DEFAULT_LIFE;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 21;
    initialization->sprite.sizeY = 11;
    initialization->sprite.path = "media/sprites/daggerA_b.png";
    return initialization;
}

server::hp_t GreenPlayer::WallAttack::WallElement::getDamage() {
    return DEFAULT_DAMAGE;
}

server::Tribool GreenPlayer::WallAttack::WallElement::collidesWith(const server::Entity &entity) {
    return entity.data.getTeam() != this->data->getTeam() ? server::T_TRUE : server::NA;
}

GreenPlayer::WallAttack::WallElement::WallElement(server::pos_t posX, server::pos_t posY, server::APlayer *owner)
        : Power(owner), mustDestroy(false), posX(posX), posY(posY)
{}

extern "C"
{
server::ADynamicObject *getInstance() {
    return (new GreenPlayer());
}
}
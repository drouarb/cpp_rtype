//
// Created by greg on 22/12/16.
//

#include "GreenPlayer.hh"
#include "../../server/include/Grid.hh"

void GreenPlayer::shoot(server::round_t round) {
//    server::Player::shoot(round);
    this->nextAttack = 0;
}

server::EntityInitialization *GreenPlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlB.png";
    return pInitialization;
}

server::ADynamicObject *GreenPlayer::createAttack(server::attackId_t id, server::round_t round)
{
    setAttackWait(id, 10, round);
    return new WallAttack(this->data->getPosX() + 10 + this->data->getSprite().sizeX, this->data->getPosY() / 2 + 12);
}

/*
 * ----------------------------------------------------------------------------------------------------------
 */

GreenPlayer::WallAttack::WallAttack(server::pos_t posX, server::pos_t posY) : posX(posX), posY(posY), initialRound(0),
                                                                              layerLeft(3), nextPlace(TOP) {}

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
        entityAction->newEntity = new WallElement(this->posX - this->data->getSprite().sizeX,
                                                  this->posY - this->data->getSprite().sizeY);
        this->layerLeft--;
    } else {
        nextPlace = DOWN;
        entityAction->newEntity = new WallElement(this->posX - this->data->getSprite().sizeX,
                                                  this->posY + this->data->getSprite().sizeY);
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

void GreenPlayer::WallAttack::WallElement::collide(const server::Entity &, server::round_t) {
    this->mustDestroy = true;
}

server::EntityAction *
GreenPlayer::WallAttack::WallElement::act(server::round_t, const server::Grid &vector) {
    server::EntityAction *action = new server::EntityAction;

    action->destroy = this->mustDestroy;
    action->speedX = 2;
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
    initialization->sprite.sizeX = 34;
    initialization->sprite.sizeY = 34;
    initialization->sprite.path = "media/sprites/magicBullet.png";
    return initialization;
}

server::hp_t GreenPlayer::WallAttack::WallElement::getDamage() {
    return DEFAULT_DAMAGE;
}

server::Tribool GreenPlayer::WallAttack::WallElement::collidesWith(const server::Entity &entity) {
    return server::T_TRUE;
}

GreenPlayer::WallAttack::WallElement::WallElement(server::pos_t posX, server::pos_t posY) : mustDestroy(false),
                                                                                            posX(posX), posY(posY) {}

extern "C"
{
server::ADynamicObject *getInstance() {
    return (new GreenPlayer());
}
}
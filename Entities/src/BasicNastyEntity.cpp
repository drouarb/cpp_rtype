//
// Created by greg on 15/12/2016.
//

#include <BasicNastyEntity.hh>

BasicNastyEntity::BasicNastyEntity() : notifyCollision(nullptr), stopwatch(IStopwatch::getInstance()) {
    this->stopwatch->set();
}

void BasicNastyEntity::collide(const server::Entity &entity) {
    this->notifyCollision = new server::EntityAction();
    this->notifyCollision->hp -= entity.obj->getDamage();
}

server::EntityAction *BasicNastyEntity::nextAction() {
    if (this->notifyCollision) {
        server::EntityAction *a = this->notifyCollision;

        this->notifyCollision = nullptr;
        return a;
    }
    server::EntityAction * a = new server::EntityAction();
    a->speedX = this->data->getVectX() - 1;

    if (this->stopwatch->ellapsedMs() > FIRE_FREQUENCY) {
        this->stopwatch->set();
        a->newEntity = new VeryNastyProjectile();
    }
    return (a);
}

server::EntityInitialization *BasicNastyEntity::initialize() {
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = DEFAULT_HP;
    return initialization;//TODO Add sprite
}

server::damage_t BasicNastyEntity::getDamage() {
    return NASTY_COLLISION_DAMAGE;
}

void BasicNastyEntity::VeryNastyProjectile::collide(const server::Entity &) {
    this->isCollide = true;
}

server::EntityAction *BasicNastyEntity::VeryNastyProjectile::nextAction() {
    server::EntityAction * a = new server::EntityAction();
    if (this->isCollide) {
        a->destroy = true;
        a->soundToPlay = ""; //TODO add EXPLOSSSSSSSSSSSSSSSSSIONNN BOUM BAM BIM BROUM
        return (a);
    }
    a->speedX = this->data->getVectX() - 10;
    return (a);
}

server::EntityInitialization *BasicNastyEntity::VeryNastyProjectile::initialize() {
    return (new server::EntityInitialization(""));//TODO Add sprite
}

server::damage_t BasicNastyEntity::VeryNastyProjectile::getDamage() {
    return NASTY_DAMAGE;
}

BasicNastyEntity::VeryNastyProjectile::VeryNastyProjectile() : isCollide(false) {}

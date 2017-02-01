//
// Created by greg on 15/12/2016.
//


#include "Definitions.hh"
#include "../../server/include/Grid.hh"
#include <Lighter.hh>
#include <entities/VisualFx.hh>

Lighter::Lighter() : lostHp(0), mustDestroy(false)
{ }

server::EntityInitialization *Lighter::initialize(server::round_t round, const server::Grid &environment)
{
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->action.hp = 100;
    initialization->team = server::Team::FOE;
    initialization->action.speedX = -3;
    initialization->action.speedY = 0;
    initialization->sprite.sizeX = 350;
    initialization->sprite.sizeY = 100;
    initialization->sprite.path = "media/sprites/bf110.png";
    this->startingRound = round;

    return initialization;
}

void Lighter::collide(const server::Entity &entity, server::round_t current_round)
{

    lostHp += entity.obj->getDamage();
    if (this->data->getHp() - lostHp <= 0)
    {
        mustDestroy = true;
    }
}

server::EntityAction *Lighter::act(server::round_t current_round, const server::Grid &)
{
    server::EntityAction * a;
    a = new server::EntityAction();
    a->destroy = mustDestroy;
    a->speedX = -3;
    a->speedY = 0;
    a->hp = this->data->getHp() - lostHp;
    lostHp = 0;

    if (mustDestroy)
    {
        a->newEntity = new server::VisualFx(data->getPosX() + 30, data->getPosY() + server::VisualFx::Y_EXPLOSION_C,
                                            "media/sprites/explosionC.png", "media/sounds/explosion1.ogg", 100,
                                            0, server::VisualFx::Y_EXPLOSION_C);
        return (a);
    }


    if (data->getPosX() > FIELD_WIDTH)
    {
        a->speedX = -5;
    }
    else
    {
        a->speedX = -3;

        if (current_round % 2 == 0)
        {
            if (current_round % 4 == 0)
            {
                Lightning *projectile = new Lightning(this->data->getPosX() + 100,
                                                      this->data->getPosY(),
                                                      -10);
                a->newEntity = projectile;
            }
            else
            {
                Lightning *projectile = new Lightning(this->data->getPosX() + 100,
                                                      this->data->getPosY() + this->data->getSprite().sizeY,
                                                      10);
                a->newEntity = projectile;
            }
        }
    }
    return (a);
}

server::hp_t Lighter::getDamage()
{
    return (32000);
}

server::Tribool Lighter::collidesWith(const server::Entity &entity)
{
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}





Lighter::Lightning::Lightning(server::speed_t posX, server::speed_t posY, server::speed_t vectY) : collides(false)
{
    this->posX = posX;
    this->posY = posY;
    this->vectY = vectY;
}

server::EntityInitialization *Lighter::Lightning::initialize(server::round_t, const server::Grid &environment)
{
    server::EntityInitialization *initialization = new server::EntityInitialization("");
    initialization->team = server::Team::FOE;
    initialization->sprite.sizeX = 14;
    initialization->sprite.sizeY = 38;
    initialization->posX = this->posX;
    initialization->posY = this->posY - initialization->sprite.sizeY / 2;
    initialization->sprite.path = "media/sprites/lightning.png";
    return initialization;
}

void Lighter::Lightning::collide(const server::Entity &entity, server::round_t current_round)
{
    if (entity.data.getTeam() == server::Team::FOE)
    {
        return;
    }
    collides = true;
}

server::EntityAction *Lighter::Lightning::act(server::round_t current_round, const server::Grid &)
{
    server::EntityAction * a = new server::EntityAction();

    if (collides)
    {
        a->destroy = true;
        a->soundToPlay = "";
        return (a);
    }

    a->speedX = -3;
    a->speedY = vectY;
    return (a);
}

server::hp_t Lighter::Lightning::getDamage()
{
    return 10;
}

server::Tribool Lighter::Lightning::collidesWith(const server::Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? server::T_TRUE : server::T_FALSE);
}




extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new Lighter());
}
}

//
// Created by greg on 15/12/2016.
//

#ifndef CPP_RTYPE_ZEPPELIN_HH
#define CPP_RTYPE_ZEPPELIN_HH

#include <entities/ADynamicObject.hh>
#include <entities/Entity.hh>
#include <helpers/IStopwatch.hh>
#include <vector>
#include "../../server/include/Grid.hh"

class Zeppelin : public server::ADynamicObject {

private:
    server::hp_t lostHp;
    bool mustDestroy;
    server::round_t startRound;

    static const int density = 10;

public:
    server::Tribool collidesWith(const server::Entity &entity) override;

    Zeppelin();

    void collide(const server::Entity &entity, server::round_t current_round) override;
    server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
    server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

    server::hp_t getDamage() override;


private:

    class Hitbox : public server::ADynamicObject {
    private:

        server::pos_t x_offset;
        server::ADynamicObject * owner;

    public:

        void setOwner(server::ADynamicObject * owner, server::pos_t x_offset);

        void collide(const server::Entity &entity, server::round_t current_round) override;

        server::EntityAction *act(server::round_t current_round, const server::Grid &vector) override;

        server::EntityInitialization *initialize(server::round_t round, const server::Grid &vector) override;

        server::hp_t getDamage() override;

        server::Tribool collidesWith(const server::Entity &entity) override;
    };



    class NovaMissile : public server::ADynamicObject
    {
    private:
        bool mustDestroy;
        server::pos_t posX;
        server::pos_t posY;
        int nb;
        server::round_t startRound;
        double angle;

        static const int speed = 3;
        static const double startingAngle[8];

    public:
        NovaMissile(server::pos_t posX, server::pos_t posY, int nb, double angle);

        void collide(const server::Entity &entity, server::round_t current_round) override;

        server::EntityAction *act(server::round_t current_round, const server::Grid &environment) override;

        server::EntityInitialization *initialize(server::round_t round, const server::Grid &environment) override;

        server::hp_t getDamage() override;

        server::Tribool collidesWith(const server::Entity &entity) override;
    };
};


#endif //CPP_RTYPE_ZEPPELIN_HH

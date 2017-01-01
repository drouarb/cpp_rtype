//
// Created by greg on 15/12/2016.
//

#ifndef CPP_RTYPE_LIGHTER_HH
#define CPP_RTYPE_LIGHTER_HH

#include <entities/ADynamicObject.hh>
#include <entities/Entity.hh>
#include <helpers/IStopwatch.hh>
#include <vector>
#include "../../server/include/Grid.hh"

class Lighter : public server::ADynamicObject {

private:
    server::hp_t lostHp;
    bool mustDestroy;
    server::round_t startingRound;

public:
    server::Tribool collidesWith(const server::Entity &entity) override;

    Lighter();

    void collide(const server::Entity &entity, server::round_t current_round) override;
    server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
    server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

    server::hp_t getDamage() override;


private:
    class Lightning : public server::ADynamicObject
    {
    private:
        server::pos_t posX;
        server::pos_t posY;
        bool collides;

    public:
        Lightning(server::speed_t posX, server::speed_t posY, server::speed_t vectY);

        void collide(const server::Entity &, server::round_t current_round) override;
        server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
        server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

        server::Tribool collidesWith(const server::Entity &entity) override;

    private:
        server::hp_t getDamage() override;

        server::speed_t vectY;

    };
};


#endif //CPP_RTYPE_LIGHTER_HH

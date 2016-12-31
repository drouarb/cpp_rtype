//
// Created by greg on 15/12/2016.
//

#ifndef CPP_RTYPE_BOMBER_HH
#define CPP_RTYPE_BOMBER_HH


#include <entities/ADynamicObject.hh>
#include <entities/Entity.hh>
#include <helpers/IStopwatch.hh>
#include <vector>
#include "../../server/include/Grid.hh"

class Bomber : public server::ADynamicObject {
private:

    class BomberProjectile : public server::ADynamicObject {
    private:
        bool collides;

    public:
        BomberProjectile(server::speed_t posX, server::speed_t posY);

        void collide(const server::Entity &, server::round_t current_round) override;
        server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
        server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

        server::Tribool collidesWith(const server::Entity &entity) override;

    private:
        server::hp_t getDamage() override;

        server::speed_t posX;
        server::speed_t posY;


    };

private:
    server::hp_t lostHp;
    bool mustDestroy;
    server::round_t startingRound;

    static const int NASTY_DAMAGE = 15;
    static const int DEFAULT_HP = 70;


public:
    server::Tribool collidesWith(const server::Entity &entity) override;

    Bomber();

    void collide(const server::Entity &entity, server::round_t current_round) override;
    server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
    server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

    server::hp_t getDamage() override;
};


#endif //CPP_RTYPE_BOMBER_HH

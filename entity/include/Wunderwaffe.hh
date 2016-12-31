//
// Created by greg on 30/12/16.
//

#ifndef CPP_RTYPE_WUNDERWAFFE_HH
#define CPP_RTYPE_WUNDERWAFFE_HH


static const int DEFAULT_LIFE = 1000;

#include <entities/Player.hh>
#include "../../server/include/Grid.hh"

class Wunderwaffe : public server::ADynamicObject {
private:
    static const int DEFAULT_DAMAGE = 40;
    static const int MAX_MOVEMENT = 100;

    enum movement_t {
        FRONT,
        BACK
    };


    class ClassicBullet : public server::ADynamicObject {

    };

    class BigBullet : public server::ADynamicObject {
    private:
        static const int DEFAULT_DAMAGE = 40;

        bool mustDestroy;
        server::round_t startRound;

        server::pos_t posX;
        server::pos_t posY;

    public:

        BigBullet(server::pos_t posX, server::pos_t posY);

        void collide(const server::Entity &entity, server::round_t current_round) override;

        server::EntityAction *act(server::round_t current_round, const server::Grid &environment) override;

        server::EntityInitialization *initialize(server::round_t round, const server::Grid &environment) override;

        server::hp_t getDamage() override;

        server::Tribool collidesWith(const server::Entity &entity) override;
    };

    server::hp_t damage;
    server::round_t startRound;
    server::pos_t pos;

public:
    void collide(const server::Entity &entity, server::round_t current_round) override;

    server::EntityAction *act(server::round_t current_round, const server::Grid &vector) override;

    server::EntityInitialization *initialize(server::round_t round, const server::Grid &vector) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;
};


#endif //CPP_RTYPE_WUNDERWAFFE_HH

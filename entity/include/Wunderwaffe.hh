//
// Created by greg on 30/12/16.
//

#ifndef CPP_RTYPE_WUNDERWAFFE_HH
#define CPP_RTYPE_WUNDERWAFFE_HH


static const int DEFAULT_LIFE = 1000;

#include <entities/Player.hh>

class Wunderwaffe : public server::ADynamicObject {
private:
    static const int DEFAULT_DAMAGE = 40;



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

        server::EntityAction *act(server::round_t current_round, const std::vector<server::Entity *> &vector) override;

        server::EntityInitialization *initialize(server::round_t round, const std::vector<server::Entity *> &vector) override;

        server::hp_t getDamage() override;

        server::Tribool collidesWith(const server::Entity &entity) override;
    };

    server::hp_t damage;
    server::round_t startRound;

public:
    void collide(const server::Entity &entity, server::round_t current_round) override;

    server::EntityAction *act(server::round_t current_round, const std::vector<server::Entity *> &vector) override;

    server::EntityInitialization *initialize(server::round_t round, const std::vector<server::Entity *> &vector) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;
};


#endif //CPP_RTYPE_WUNDERWAFFE_HH

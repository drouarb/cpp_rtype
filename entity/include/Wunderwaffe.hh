//
// Created by greg on 30/12/16.
//

#ifndef CPP_RTYPE_WUNDERWAFFE_HH
#define CPP_RTYPE_WUNDERWAFFE_HH


static const int DEFAULT_LIFE = 1000;

#include <entities/Player.hh>


class Wunderwaffe : server::ADynamicObject {
private:
    static const int DEFAULT_DAMAGE = 40;



    class ClassicBullet : server::ADynamicObject {

    };



public:
    void collide(const server::Entity &entity, server::round_t current_round) override;

    server::EntityAction *act(server::round_t current_round, const std::vector<server::Entity *> &vector) override;

    server::EntityInitialization *initialize(server::round_t round, const std::vector<server::Entity *> &vector) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;
};


#endif //CPP_RTYPE_WUNDERWAFFE_HH

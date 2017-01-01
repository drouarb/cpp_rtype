//
// Created by greg on 30/12/16.
//

#ifndef CPP_RTYPE_CRAZYENTITY_HH
#define CPP_RTYPE_CRAZYENTITY_HH


#include <entities/ADynamicObject.hh>

class CrazyEntity : public server::ADynamicObject {

private:
    server::hp_t lostHp;
    bool mustDestroy;
    server::round_t startingRound;

    static const int DEFAULT_HP = 100;
    static const int SPEED = 5;

    class CrazyProjectile : public server::ADynamicObject {
    private:
        server::round_t isCollide;
        static const int DAMMAGE = 5;


    public:
        CrazyProjectile(server::speed_t posX, server::speed_t posY);

        void collide(const server::Entity &, server::round_t current_round) override;
        server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
        server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

        server::Tribool collidesWith(const server::Entity &entity) override;

    private:
        server::hp_t getDamage() override;

        server::speed_t posX;
        server::speed_t posY;


    };


public:
    CrazyEntity();

    void collide(const server::Entity &entity, server::round_t current_round) override;
    server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
    server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;

private:
    bool destroyed;
};


#endif //CPP_RTYPE_CRAZYENTITY_HH

//
// Created by greg on 15/12/2016.
//

#ifndef CPP_RTYPE_BASICNASTYENTITY_HH
#define CPP_RTYPE_BASICNASTYENTITY_HH


#include <entities/ADynamicObject.hh>
#include <entities/Entity.hh>
#include <helpers/IStopwatch.hh>

class BasicNastyEntity : public server::ADynamicObject {
private:

    class VeryNastyProjectile : public server::ADynamicObject {
    private:
        bool isCollide = false;

    public:
        VeryNastyProjectile();

        void collide(const server::Entity &) override ;
        server::EntityAction *nextAction() override ;
        server::EntityInitialization *initialize() override ;

    private:
        server::damage_t getDamage() override;

    };

private:
    server::EntityAction *notifyCollision;
    IStopwatch *stopwatch;

    static const int NASTY_DAMAGE = 10;
    static const int NASTY_COLLISION_DAMAGE = 5;
    static const int FIRE_FREQUENCY = 5000;
    static const int DEFAULT_HP = 100;


public:
    BasicNastyEntity();

//    friend std::ostream &operator<<(std::ostream &os, const BasicNastyEntity &entity);

    void collide(const server::Entity &) override ;
    server::EntityAction *nextAction() override ;
    server::EntityInitialization *initialize() override ;

    server::damage_t getDamage() override;
};


#endif //CPP_RTYPE_BASICNASTYENTITY_HH

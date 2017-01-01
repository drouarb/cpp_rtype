//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_REDPLAYER_HH
#define CPP_RTYPE_REDPLAYER_HH

#include <entities/Player.hh>

class RedPlayer : public server::Player {
protected:

    server::ADynamicObject * createAttack(server::attackId_t id, server::round_t round) override;

    server::EntityInitialization *initialize(server::round_t, const server::Grid &) override;

private:
    
    class RegenMissile : public server::ADynamicObject, private server::Player::Power
    {
    private:
        bool mustDestroy;
        server::pos_t posX;
        server::pos_t posY;

    public:
        RegenMissile(server::APlayer * owner, server::pos_t posX, server::pos_t posY);

        void collide(const server::Entity &entity, server::round_t current_round) override;

        server::EntityAction *act(server::round_t current_round, const server::Grid &environment) override;

        server::EntityInitialization *initialize(server::round_t round, const server::Grid &environment) override;

        server::hp_t getDamage() override;

        server::Tribool collidesWith(const server::Entity &entity) override;
    };

};


#endif //CPP_RTYPE_REDPLAYER_HH

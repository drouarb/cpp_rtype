//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_YELLOWPLAYER_HH
#define CPP_RTYPE_YELLOWPLAYER_HH


#include <entities/Player.hh>

class YellowPlayer : public server::Player {
public:
    server::EntityInitialization *initialize(server::round_t round, const server::Grid &entity) override;

    server::ADynamicObject *createAttack(server::attackId_t id, server::round_t round) override;
};


#endif //CPP_RTYPE_YELLOWPLAYER_HH

//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_YELLOWPLAYER_HH
#define CPP_RTYPE_YELLOWPLAYER_HH


#include <entities/Player.hh>

class YellowPlayer : public server::Player {
public:
    void shoot(server::round_t attackId) override;

    server::EntityInitialization *initialize(server::round_t round, const std::vector<server::Entity *> &entity) override;
};


#endif //CPP_RTYPE_YELLOWPLAYER_HH

//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_REDPLAYER_HH
#define CPP_RTYPE_REDPLAYER_HH

#include <entities/Player.hh>

class RedPlayer : public server::Player {
public:
    void shoot(server::round_t round) override;

    server::EntityInitialization *initialize(server::round_t, const std::vector<server::Entity *> &) override;

private:


};


#endif //CPP_RTYPE_REDPLAYER_HH

//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_BLUEPLAYER_HH
#define CPP_RTYPE_BLUEPLAYER_HH


#include <entities/Player.hh>

class BluePlayer : public server::Player {
public:
    server::EntityInitialization *initialize(server::round_t, const server::Grid &) override;
};


#endif //CPP_RTYPE_BLUEPLAYER_HH

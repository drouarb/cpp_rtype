//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PLAYER_HH
#define CPP_RTYPE_PLAYER_HH

#include "IPlayer.hh"
#include "definitions.hh"
#include "IEntity.hh"

namespace server {
    class Player : public IPlayer, public IEntity {
        void shoot(attackId_t attackId) override;
    };
}

#endif //CPP_RTYPE_PLAYER_HH

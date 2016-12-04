//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_ATTACK_HH
#define CPP_RTYPE_ATTACK_HH

#include <string>
#include <ostream>
#include "AEntity.hh"

namespace Server {

    struct Attack {
        std::string soundFile;
        std::string sprite;
        AEntity::damagePoint_t damage;
        uint16_t recharge;
        uint16_t nbHits;

        Attack(const std::string &soundFile, const std::string &sprite, AEntity::damagePoint_t damage,
               uint16_t recharge, uint16_t nbHits);

    };
    std::ostream &operator<<(std::ostream &os, const Attack &attack);
}

#endif //CPP_RTYPE_ATTACK_HH

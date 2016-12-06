#ifndef RTYPE_SPAWN_HH_
#define RTYPE_SPAWN_HH_

#include "definitions.hh"
#include "IEntity.hh"

namespace server
{
    struct Spawn
    {
        Spawn();
        Spawn(const Spawn &);
        ~Spawn();

        Spawn & operator=(const Spawn &);

        std::string dlName;
        round_t time;
        pos_t posX;
        pos_t posY;

        IEntity * trigger();
    };
}

#endif
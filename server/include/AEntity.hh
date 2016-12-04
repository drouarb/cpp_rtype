//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_AENTITY_HH
#define CPP_RTYPE_AENTITY_HH

#include <cstdint>
#include <string>
#include <cstdbool>
#include "IEntity.hh"

extern "C" {
    Server::IEntity *create_entity(uint16_t entityId);
};
namespace Server {

    typedef uint16_t EntityId;
    typedef int8_t TeamId;

    class AEntity : public IEntity {
    private:
        const EntityId entityId;
    public:
        typedef uint32_t damagePoint_t;
        AEntity(const EntityId entityId, const std::string &sprite);

    protected:
        const std::string sprite;
        uint16_t posX;
        uint16_t posY;
        int16_t speedX;
        int16_t speedY;
        int16_t hp;
        TeamId teamId;
        bool destroyed;
    public:

    };

}

#endif //CPP_RTYPE_AENTITY_HH

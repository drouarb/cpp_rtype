//
// Created by lewis_e on 13/12/16.
//

#ifndef CPP_RTYPE_ENTITY_HH
#define CPP_RTYPE_ENTITY_HH

#include "ADynamicObject.hh"

namespace server
{
    class Entity
    {
    public:
        Entity();
        Entity(ADynamicObject * obj, entityId_t id);
        ~Entity();

        void initialize(ADynamicObject * obj, entityId_t id);

        ADynamicObject * obj;
        EntityData data;

        static Entity * make(const std::string & path, entityId_t id);
    };
}

#endif //CPP_RTYPE_ENTITY_HH

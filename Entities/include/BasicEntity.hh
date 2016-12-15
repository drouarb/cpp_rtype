//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_BASICENTITY_HH
#define CPP_RTYPE_BASICENTITY_HH


#include <ostream>
#include "entities/ADynamicObject.hh"
#include "definitions.hh"

class BasicEntity : public server::ADynamicObject {
public:
    BasicEntity();

//    friend std::ostream &operator<<(std::ostream &os, const BasicEntity &entity);

    void collide(const server::Entity &) override ;
    server::EntityAction *nextAction() override ;
    server::EntityInitialization *initialize() override ;

    server::damage_t getDamage() override;

private:
    bool destroyed;
};



#endif //CPP_RTYPE_BASICENTITY_HH

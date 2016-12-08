//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_BASICENTITY_HH
#define CPP_RTYPE_BASICENTITY_HH


#include <ostream>
#include "../../server/include/IEntity.hh"
#include "../../server/include/definitions.hh"

class BasicEntity : public server::IEntity {
public:
    BasicEntity();

    friend std::ostream &operator<<(std::ostream &os, const BasicEntity &entity);

    void setEntityId(server::entityId_t);
    server::entityId_t getEntityId();
    server::Team getTeam();
    std::string & getSprite();
    void setPosX(server::pos_t);
    server::pos_t getPosX();
    void setPosY(server::pos_t);
    server::pos_t getPosY();
    void setSpeedX(server::speed_t);
    server::speed_t getSpeedX();
    void setSpeedY(server::speed_t);
    server::speed_t getSpeedY();
    void modHp(int);
    int getHp();
    void destroy();
    void restore();
    bool isDestroyed();

    void collide(server::IEntity *) final;
    server::EntityAction *nextAction() final;
    
private:
    server::entityId_t id;
    server::Team  team;
    std::string sprite;
    server::pos_t posX;
    server::pos_t posY;
    server::speed_t speedX;
    server::speed_t speedY;
    int hp;
    bool destroyed;
};



#endif //CPP_RTYPE_BASICENTITY_HH

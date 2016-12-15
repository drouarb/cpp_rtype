//
// Created by lewis_e on 12/12/16.
//

#ifndef CPP_RTYPE_ENTITYDATA_HH
#define CPP_RTYPE_ENTITYDATA_HH

#include "definitions.hh"
#include "EntityInitialization.hh"
#include "Sprite.hh"

namespace server
{
    class EntityData
    {
    public:
        EntityData();
        ~EntityData();

        void initialize(EntityInitialization *, entityId_t);

        Team getTeam() const;

        void setTeam(Team team);

        const Sprite &getSprite() const;

        void setSprite(const Sprite &);

        entityId_t getId() const;

        void setId(entityId_t id);

        pos_t getPosX() const;

        void setPosX(pos_t posX);

        pos_t getPosY() const;

        void setPosY(pos_t posY);

        speed_t getVectX() const;

        void setVectX(speed_t vectX);

        speed_t getVectY() const;

        void setVectY(speed_t vectY);

        int getHp() const;

        void setHp(int hp);

        bool isDestroyed() const;

        void setDestroyed(bool destroyed);

    private:
        Team team;
        Sprite sprite;
        entityId_t id;
        pos_t posX;
        pos_t posY;
        speed_t vectX;
        speed_t vectY;
        int hp;
        bool destroyed;
    };
}

#endif //CPP_RTYPE_ENTITYDATA_HH

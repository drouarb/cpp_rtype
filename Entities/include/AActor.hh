//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_AACTOR_HH
#define CPP_RTYPE_AACTOR_HH


#include <vector>
#include "../../../Entities/include/Attack.hh"
#include "IEntity.hh"


namespace server {

    class AActor : public server::IEntity {
    private:
        int hp;
        bool destroyed;


    public:
        AActor(const server::entityId_t entityId);

        void play(std::vector<server::IEntity *>);

        virtual void hit(int damage);


        bool isDestroyed() override;
    };

}

#endif //CPP_RTYPE_AACTOR_HH

//
// Created by lewis_e on 28/12/16.
//

#ifndef CPP_RTYPE_COLLISIONWALL_HH
#define CPP_RTYPE_COLLISIONWALL_HH

#include "EntityAction.hh"

namespace server
{
    enum Axis
    {
        X,
        Y
    };

    enum Direction
    {
        POS,
        NEG
    };

    class CollisionWall
    {
    public:
        CollisionWall();
        CollisionWall(const CollisionWall & other);
        ~CollisionWall();

        CollisionWall &operator=(const CollisionWall & other);

        void add(Axis axis, Direction dir);

        void apply(EntityAction * action);

    private:
        bool x_pos;
        bool x_neg;
        bool y_pos;
        bool y_neg;
    };
}


#endif //CPP_RTYPE_COLLISIONWALL_HH

//
// Created by lewis_e on 28/12/16.
//

#ifndef CPP_RTYPE_COLLISIONWALL_HH
#define CPP_RTYPE_COLLISIONWALL_HH

namespace server
{
	struct EntityAction;

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

        void add(Axis axis, Direction dir, const Entity * entity);
        void apply(EntityAction * action);
        bool isSet() const;
        void reset();
        bool includes(const Entity * entity) const;

    private:
        bool x_pos;
        bool x_neg;
        bool y_pos;
        bool y_neg;
        bool is_set;
        std::vector<const Entity*> collisions;
    };
}


#endif //CPP_RTYPE_COLLISIONWALL_HH

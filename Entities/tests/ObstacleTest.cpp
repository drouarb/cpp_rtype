//
// Created by greg on 02/12/2016.
//

#include <cassert>
#include <Obstacle.hh>

int main()
{
    server::IEntity *pEntity = create_entity(43);
    Obstacle *obstacle = dynamic_cast<Obstacle *>(pEntity);
    assert(obstacle != nullptr);
    return 0;
}
//
// Created by greg on 02/12/2016.
//

#include <Projectile.hh>
#include <cassert>

int main()
{
    Server::IEntity *pEntity = create_entity(43);
    Projectile *projectile = dynamic_cast<Projectile *>(pEntity);
    assert(projectile != nullptr);

    return 0;
}
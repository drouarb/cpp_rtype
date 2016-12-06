//
// Created by greg on 02/12/2016.
//

#include <BasicEntity.hh>
#include <cassert>
#include <iostream>


int main()
{
    std::cout << "TEST" << std::endl;


    server::IEntity *pEntity = create_entity(43);
    BasicEntity *basicEntity = dynamic_cast<BasicEntity *>(pEntity);
    assert(basicEntity != nullptr);
    return 0;
}
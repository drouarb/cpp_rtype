//
// Created by lewis_e on 15/12/16.
//

#ifndef CPP_RTYPE_SPRITE_HH
#define CPP_RTYPE_SPRITE_HH

#include "definitions.hh"
#include <string>

namespace server
{
    struct Sprite
    {
        Sprite();
        Sprite(const std::string & path);
        Sprite(const Sprite & other);
        ~Sprite();

        bool operator==(const Sprite & other);
        Sprite &operator=(const Sprite & other);

        std::string path;
        pos_t sizeX;
        pos_t sizeY;
    };
}

#endif //CPP_RTYPE_SPRITE_HH

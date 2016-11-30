//
// Created by jonas_e on 11/26/16.
//

#ifndef CPP_RTYPE_ITEM_HH
#define CPP_RTYPE_ITEM_HH

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "AItem.hh"

namespace UI {
    class Item : public AItem {
    public:
        Item();
        void setImage(std::string filename);
        void setPosition(unsigned int posX, unsigned int posY);
        sf::Sprite getSprite();

    private:
        sf::Sprite sprite;
    };
}

#endif //CPP_RTYPE_ITEM_HH

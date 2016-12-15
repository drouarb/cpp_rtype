//
// Created by jonas_e on 11/26/16.
//

#ifndef CPP_RTYPE_ITEM_HH
#define CPP_RTYPE_ITEM_HH

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "AItem.hh"

namespace UI {
    class Item : public AItem {
    public:
        Item(itemType type);
        virtual ~Item();
        void setImage(std::string filename);
        void setPosition(float posX, float posY);
        void moveX(float range);
        void moveY(float range);
        sf::Sprite getSprite();

    private:
        sf::Sprite sprite;
        sf::Texture texture;
    };
}

#endif //CPP_RTYPE_ITEM_HH

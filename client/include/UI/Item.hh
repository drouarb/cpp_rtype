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
        void setImage();
        void setPosition(float posX, float posY);
        void setRatio(float ratio);
        void setRatio(float sizeXMax, float sizeYMax);
        void moveX(float range);
        void moveY(float range);
        sf::Sprite getSprite();
        void setTexture(sf::Texture*);
        void addTexture(sf::Texture *_texture, animationType type);
        void changeStatus(animationType type);

    private:
        sf::Sprite sprite;
        std::vector<sf::Texture*> textures;
        sf::Texture *texture;
    };
}

#endif //CPP_RTYPE_ITEM_HH

//
// Created by jonas_e on 11/26/16.
//

#ifndef CPP_RTYPE_ITEM_HH
#define CPP_RTYPE_ITEM_HH

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <list>
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
        void addTexture(sf::Texture *_texture, UI::animationType type);
        void changeStatus(UI::animationType type);
        void addAnimation(UI::animationType animationType, short frames, unsigned int posX, unsigned int posY, unsigned int width,
                          unsigned int height);
        void addAnimation(UI::animationType animationType, short frames, unsigned int size);

    private:
        sf::Sprite sprite; // le changer en pointeur pour faciliter l'échange
        std::vector<sf::Texture*> textures;
        std::vector<std::list<sf::Sprite*>> animations;
        std::list<sf::Sprite*> *animation;
        sf::Texture *texture;
        float px;
        float py;
        unsigned short animationTick;
    };
}

#endif //CPP_RTYPE_ITEM_HH

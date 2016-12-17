//
// Created by jonas_e on 11/25/16.
//

#ifndef CPP_RTYPE_ITEMFACTORY_HH
#define CPP_RTYPE_ITEMFACTORY_HH

#include <SFML/Graphics/Texture.hpp>
#include "Item.hh"
#include "AItem.hh"

namespace UI {
    class ItemFactory {
    public:
        ItemFactory();
        ~ItemFactory();

        AItem* instantiate(UI::itemType type, const std::string &texturePath);
        typedef UI::AItem* (*instantiateItem)();

    private:
        static AItem* instantiateButton();
        static AItem* instantiateNormalItem();
        static AItem* instantiateBackgroundObject();
        static AItem* instantiateBackground();
        void setTexture(UI::Item* item);
        const static std::map<UI::itemType, instantiateItem> itemMap;
        std::map<std::string, sf::Texture*> textureMap;
        std::string texturePath;
    };
}


#endif //CPP_RTYPE_ITEMFACTORY_HH

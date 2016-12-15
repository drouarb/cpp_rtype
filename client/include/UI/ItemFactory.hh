//
// Created by jonas_e on 11/25/16.
//

#ifndef CPP_RTYPE_ITEMFACTORY_HH
#define CPP_RTYPE_ITEMFACTORY_HH

#include "AItem.hh"

namespace UI {
    class ItemFactory {
    public:
        ItemFactory();
        ~ItemFactory();

        static AItem* instantiate(UI::itemType type);
        typedef UI::AItem* (*instantiateItem)();

    private:
        static AItem* instantiateButton();
        static AItem* instantiateNormalItem();
        static AItem *instantiateBackgroundObject();
        static AItem *instantiateBackground();
        const static std::map<UI::itemType, instantiateItem> itemMap;
    };
}


#endif //CPP_RTYPE_ITEMFACTORY_HH

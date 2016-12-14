//
// Created by jonas_e on 11/23/16.
//

#ifndef CPP_RTYPE_ILAYER_HH
#define CPP_RTYPE_ILAYER_HH

#include "AItem.hh"

namespace UI {
    class ILayer {
    public:
        virtual ~ILayer(){};
        virtual unsigned long addItem(UI::itemType type, std::string sprite, int posX, int posY) = 0;
        virtual AItem *getItem(unsigned long itemID) = 0;
        virtual std::vector<AItem *> getItems() = 0;
    };
}


#endif //CPP_RTYPE_ILAYER_HH

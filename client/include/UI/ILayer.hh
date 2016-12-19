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
        virtual AItem *addItem(UI::itemType type, const std::string& sprite, int posX, int posY) = 0;
        virtual void addTexture(UI::AItem *item, UI::animationType type, const std::string& sprite) = 0;
        virtual AItem *getItem(unsigned long itemID) = 0;
        virtual std::vector<AItem *>& getItems() = 0;
        virtual void action() = 0;
        virtual void open() = 0;
        virtual void close() = 0;
        virtual bool isVisible() = 0;

    protected:
        bool visible;
    };
}


#endif //CPP_RTYPE_ILAYER_HH

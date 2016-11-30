#ifndef CPP_RTYPE_ALAYER_HH
#define CPP_RTYPE_ALAYER_HH

#include "ILayer.hh"
#include "AItem.hh"
#include "ItemFactory.hh"

namespace UI {

    enum layerType {
        MENU,
        HUD,
        GAME,
        BACKGROUND,
        LAYERS_NUMBER
    };

    class ALayer : public ILayer {
    public:
        ALayer();
        ~ALayer();
        unsigned long addItem(UI::itemType type, std::string sprite, int posX, int posY);
        AItem *getItem(unsigned long itemID);
    private:
        std::vector<AItem*> items;
        ItemFactory* itemFactory;
        std::vector<AItem *> getItems();
    };
}


#endif //CPP_RTYPE_ALAYER_HH

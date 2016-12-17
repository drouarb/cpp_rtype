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
        BACKGROUNDS,
        LAYERS_NUMBER
    };

    class ALayer : public ILayer {
    public:
        ALayer();
        ~ALayer();

        UI::AItem *addItem(UI::itemType type, const std::string& sprite, int posX, int posY);
        UI::AItem *getItem(unsigned long itemID);
        void open();
        void close();
        bool isVisible();

    protected:
        std::vector<AItem*> items;
        ItemFactory* itemFactory;
        std::vector<AItem *> getItems();
    };
}


#endif //CPP_RTYPE_ALAYER_HH

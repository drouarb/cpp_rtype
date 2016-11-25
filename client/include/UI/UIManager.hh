#ifndef UIMANAGER_HH_
#define UIMANAGER_HH_

#include <vector>
#include "IWindow.hh"
#include "ItemFactory.hh"
#include "ALayer.hh"

namespace UI {
    class UIManager {
    public:
        UIManager();
        ~UIManager();

        void init();
        int addLayer(UI::layerType, UI::windowType windowType);
        int addItemToLayer(UI::itemType type, std::string sprite, int posX, int posY, unsigned long LayerID);
        int addItemToGame(UI::itemType type, std::string sprite, int posX, int posY);
        IWindow* getWindow(enum windowType);

    private:
        std::vector<UI::IWindow*> windows;
    };
}

#endif
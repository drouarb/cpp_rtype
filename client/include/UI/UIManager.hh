#ifndef UIMANAGER_HH_
#define UIMANAGER_HH_

#include <vector>
#include "IWindow.hh"
#include "ItemFactory.hh"
#include "ALayer.hh"
#include "IAudioManager.hh"

namespace UI {
    class UIManager {
    public:
        UIManager();
        ~UIManager();

        void init();
        int addLayer(UI::layerType, UI::windowType windowType);
        unsigned long addItemToLayer(UI::itemType type, std::string sprite, int posX, int posY, unsigned long LayerID);
        int addItemToGame(UI::itemType type, std::string sprite, int posX, int posY);
        int UpdateItem(unsigned long layerID, unsigned long itemID);
        IWindow* getWindow(enum windowType);
        IAudioManager* getAudioManager();

    private:
        std::vector<UI::IWindow*> windows;
        IAudioManager *audioManager;
    };
}

#endif
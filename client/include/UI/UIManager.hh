#ifndef UIMANAGER_HH_
#define UIMANAGER_HH_

#include <vector>
#include "IWindow.hh"

namespace UI {

    enum windowType {
        MAIN_WINDOW
    };

    class UIManager {
    public:
        UIManager();
        ~UIManager();

        void init();
        IWindow* getWindow(enum windowType);

    private:
        std::vector<UI::IWindow*> windows;
    };
}

#endif
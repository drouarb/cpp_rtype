//
// Created by jonas_e on 12/21/16.
//

#ifndef CPP_RTYPE_MENULAYER_HH
#define CPP_RTYPE_MENULAYER_HH

#include "ALayer.hh"
#include "Text.hh"
#include "Window.hh"

namespace UI {
    class MenuLayer : public ALayer {
    public:
        MenuLayer();
        void init(sf::RenderWindow *win);
        void action();
        Text * addTextBox(float x, float y);

    private:
        std::vector<UI::Text*> textBoxes;
        sf::RenderWindow *window;
    };
}


#endif //CPP_RTYPE_MENULAYER_HH

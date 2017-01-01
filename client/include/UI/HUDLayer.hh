//
// Created by jonas_e on 12/27/16.
//

#ifndef CPP_RTYPE_HUDLAYER_HH
#define CPP_RTYPE_HUDLAYER_HH


#include "ALayer.hh"

#include "ALayer.hh"
#include "Text.hh"
#include "Window.hh"

namespace UI {
    class HUDLayer : public ALayer {
    public:
        HUDLayer();
        void init(sf::RenderWindow *win);
        void action();
        Text * addTextBox(float x, float y);

    private:
        std::vector<UI::Text*> textBoxes;
        sf::RenderWindow *window;
    };
}

class HUDLayer {

};


#endif //CPP_RTYPE_HUDLAYER_HH

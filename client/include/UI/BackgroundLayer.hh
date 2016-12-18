//
// Created by jonas_e on 12/2/16.
//

#ifndef CPP_RTYPE_BACKGROUNDLAYER_HH
#define CPP_RTYPE_BACKGROUNDLAYER_HH

#include "ALayer.hh"
#include "Background.hh"

namespace UI {
    class BackgroundLayer : public ALayer {
    public:
        BackgroundLayer();
        void setBackground(UI::itemType type, const std::string& sprite);
        void action();

    private:
        UI::Background *backgroundOrigin;
        UI::Background *backgroundDupplication;
        std::vector<UI::AItem*> save;
    };
}


#endif //CPP_RTYPE_BACKGROUNDLAYER_HH

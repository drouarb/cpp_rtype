//
// Created by jonas_e on 12/2/16.
//

#ifndef CPP_RTYPE_BACKGROUNDLAYER_HH
#define CPP_RTYPE_BACKGROUNDLAYER_HH

#include "ALayer.hh"

namespace UI {
    class BackgroundLayer : public ALayer {

        BackgroundLayer();
        std::vector<AItem *> getItems();
        unsigned long addItem(itemType type, std::string sprite, int posX, int posY);
    };
}


#endif //CPP_RTYPE_BACKGROUNDLAYER_HH

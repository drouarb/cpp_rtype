//
// Created by jonas_e on 12/27/16.
//

#ifndef CPP_RTYPE_HUDLAYER_HH
#define CPP_RTYPE_HUDLAYER_HH


#include "ALayer.hh"

namespace UI {
    class HUDLayer : public ALayer {
    public:
        HUDLayer();
        ~HUDLayer();
        void action();

        void loadAvatar(std::string filename);
    };
}

class HUDLayer {

};


#endif //CPP_RTYPE_HUDLAYER_HH

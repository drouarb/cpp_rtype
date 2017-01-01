//
// Created by jonas_e on 11/23/16.
//

#ifndef CPP_RTYPE_GAMELAYER_HH
#define CPP_RTYPE_GAMELAYER_HH

#include "ALayer.hh"

namespace UI {
    class GameLayer : public ALayer {
    public:
        GameLayer();
        ~GameLayer();
        void action();
    };
}


#endif //CPP_RTYPE_GAMELAYER_HH

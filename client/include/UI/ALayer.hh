#ifndef CPP_RTYPE_ALAYER_HH
#define CPP_RTYPE_ALAYER_HH

#include "ILayer.hh"

namespace UI {

    enum layerType {
        MENU,
        HUD,
        GAME,
        BACKGROUND,
        LAYERS_NUMBER
    };

    class ALayer : public ILayer {
    public:
    private:
    };
}


#endif //CPP_RTYPE_ALAYER_HH

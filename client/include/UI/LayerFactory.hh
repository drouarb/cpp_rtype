#ifndef CPP_RTYPE_LAYERFACTORY_HH
#define CPP_RTYPE_LAYERFACTORY_HH

#include <map>
#include "ILayer.hh"

namespace UI {
    class LayerFactory {
        typedef UI::ILayer* (*instantiateLayer)();
        enum layerTemplate {
            MENU,
            HUD,
            GAME,
            BACKGROUND,
            SIZE
        };

        const static std::map<layerTemplate, instantiateLayer> layerMap;

    public:
        LayerFactory();
        ~LayerFactory();
        static ILayer* instantiate(layerTemplate type);

    private:
        static ILayer* instantiateMenu();
        static ILayer* instantiateHUD();
        static ILayer* instantiateGame();
        static ILayer* instantiateBackground();
    };
}


#endif //CPP_RTYPE_LAYERFACTORY_HH

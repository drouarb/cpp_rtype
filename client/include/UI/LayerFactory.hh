#ifndef CPP_RTYPE_LAYERFACTORY_HH
#define CPP_RTYPE_LAYERFACTORY_HH

#include <map>
#include "ILayer.hh"

namespace UI {

    class LayerFactory {
    public:
        LayerFactory();
        ~LayerFactory();
        static ILayer* instantiate(UI::layerType type);

    private:
        static ILayer* instantiateMenu();
        static ILayer* instantiateHUD();
        static ILayer* instantiateGame();
        static ILayer* instantiateBackground();
        typedef UI::ILayer* (*instantiateLayer)();
        const static std::map<UI::layerType, instantiateLayer> layerMap;
    };
}


#endif //CPP_RTYPE_LAYERFACTORY_HH

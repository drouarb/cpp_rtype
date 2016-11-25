//
// Created by jonas_e on 11/23/16.
//

#include <UI/UIManager.hh>
#include "../../include/UI/LayerFactory.hh"

const std::map<UI::layerType, UI::LayerFactory::instantiateLayer> UI::LayerFactory::layerMap = {
        {MENU, &instantiateMenu},
        {HUD, &instantiateHUD},
        {GAME, &instantiateGame},
        {BACKGROUND, &instantiateBackground},
};

UI::LayerFactory::LayerFactory() {

}

UI::LayerFactory::~LayerFactory() {

}

UI::ILayer *UI::LayerFactory::instantiateMenu() {
    return nullptr;
}

UI::ILayer *UI::LayerFactory::instantiateHUD() {
    return nullptr;
}

UI::ILayer *UI::LayerFactory::instantiateGame() {
    return nullptr;
}

UI::ILayer *UI::LayerFactory::instantiateBackground() {
    return nullptr;
}

UI::ILayer *UI::LayerFactory::instantiate(UI::layerType type) {
    return layerMap.at(type)();
}

//
// Created by jonas_e on 11/23/16.
//

#include <UI/UIManager.hh>
#include <UI/GameLayer.hh>
#include <UI/BackgroundLayer.hh>
#include "../../include/UI/LayerFactory.hh"

const std::map<UI::layerType, UI::LayerFactory::instantiateLayer> UI::LayerFactory::layerMap = {
        {MENU, &instantiateMenu},
        {HUD, &instantiateHUD},
        {GAME, &instantiateGame},
        {BACKGROUNDS, &instantiateBackground},
};

UI::LayerFactory::LayerFactory() {

}

UI::LayerFactory::~LayerFactory() {

}

UI::ILayer *UI::LayerFactory::instantiateMenu() {
    return static_cast<ILayer*>(new GameLayer());
}

UI::ILayer *UI::LayerFactory::instantiateHUD() {
    return static_cast<ILayer*>(new GameLayer());
}

UI::ILayer *UI::LayerFactory::instantiateGame() {
    return static_cast<ILayer*>(new GameLayer());
}

UI::ILayer *UI::LayerFactory::instantiateBackground() {
    return static_cast<ILayer*>(new BackgroundLayer());
}

UI::ILayer *UI::LayerFactory::instantiate(UI::layerType type) {
    return layerMap.at(type)();
}

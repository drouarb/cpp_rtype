//
// Created by jonas_e on 12/2/16.
//

#include <UI/Item.hh>
#include "../../include/UI/BackgroundLayer.hh"


UI::BackgroundLayer::BackgroundLayer() {
}

std::vector<UI::AItem*> UI::BackgroundLayer::getItems() {
    for (auto item : items) {
        switch (item->getType()) {
            case BACKGROUND_SLOW:
                static_cast<Item*>(item)->moveX(1);
                break;
            case BACKGROUND_MEDIUM:
                static_cast<Item*>(item)->moveX(2);
                break;
            case BACKGROUND_FAST:
                static_cast<Item*>(item)->moveX(5);
                break;
            default:
                break;
        }
    }
    return items;
}

unsigned long UI::BackgroundLayer::addItem(UI::itemType type, std::string sprite, int posX, int posY) {
    AItem* item = itemFactory->instantiate(type);
    items.push_back(item);
    return items.size() - 1;
}
#include "../../include/UI/ALayer.hh"

UI::ALayer::ALayer() {
    itemFactory = new ItemFactory();
}

UI::ALayer::~ALayer() {
    delete itemFactory;
    for (auto item : items) {
        delete item;
    }
}

UI::AItem* UI::ALayer::getItem(unsigned long itemID) {
    return items[itemID];
}

std::vector<UI::AItem*> UI::ALayer::getItems() {
    return items;
}

unsigned long UI::ALayer::addItem(UI::itemType type, std::string sprite, int posX, int posY) {
    AItem* item = itemFactory->instantiate(type);
    items.push_back(item);
    return items.size() - 1;
}

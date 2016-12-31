#include "../../include/UI/ALayer.hh"

UI::ALayer::ALayer() {
    itemFactory = new ItemFactory();
    visible = true;
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

std::vector<UI::AItem*>& UI::ALayer::getItems() {
    return items;
}

UI::AItem* UI::ALayer::addItem(UI::itemType type, const std::string& sprite, int posX, int posY) {
    AItem* item = itemFactory->instantiate(type, sprite);
    item->setImage();
    item->setPosition(posX, posY);
    items.push_back(item);
    return item;
}

bool UI::ALayer::isVisible() {
    return visible;
}

void UI::ALayer::close() {
    visible = false;
}

void UI::ALayer::open() {
    visible = true;
}

void UI::ALayer::addTexture(UI::AItem *item, UI::animationType type, const std::string &path) {
    itemFactory->addTexture(static_cast<Item*>(item), type, path);
}

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include "UI/AItem.hh"


UI::AItem::AItem(itemType t) {
    type = t;
    status = UI::IDLE;
    animated = false;
}

UI::AItem::~AItem() {

}

void    UI::AItem::setID(uint32_t id) {
    this->id = id;
}

UI::itemType UI::AItem::getType() {
    return type;
}

uint32_t UI::AItem::getID() {
    return id;
}

void UI::AItem::changeStatus(UI::animationType type) {
    status = type;
}
#include "../../include/UI/AItem.hh"

void UI::AItem::playAnimation(animationType animationType) {
    sprite.at(animationType);
}

UI::AItem::AItem() {

}

UI::AItem::~AItem() {

}

void UI::AItem::addAnimation(UI::animationType animationType, Animation animation) {
    sprite.at(animationType) = animation;
}

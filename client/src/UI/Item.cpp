//
// Created by jonas_e on 11/26/16.
//

#include <iostream>
#include "../../include/UI/Item.hh"

UI::Item::Item(itemType t) : AItem(t) {
}

void UI::Item::setImage(std::string filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load : " << filename << std::endl; // essayer de charger un placeholder à la place
    } else {
    sprite.setTexture(texture);
    }
}

void UI::Item::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Sprite UI::Item::getSprite() {
    return sprite;
}

UI::Item::~Item() {

}

void UI::Item::moveX(float range) {
    sprite.setPosition(sprite.getPosition().x + range, sprite.getPosition().y);
}

void UI::Item::moveY(float range) {
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + range);
}

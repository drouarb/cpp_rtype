//
// Created by jonas_e on 11/26/16.
//

#include <iostream>
#include "../../include/UI/Item.hh"

UI::Item::Item(itemType t) : AItem(t) {
}

void UI::Item::setImage(std::string filename) {
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load : " << filename << std::endl; // essayer de charger un placeholder à la place
    } else {
        for (int i = 0; i < UI::animationType::ANIMATIONS_NUMBER; i++) {
            textures.push_back(texture);
        }
        sprite.setTexture(*texture);
    }
}

void UI::Item::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Sprite UI::Item::getSprite() {
    return sprite;
}

void UI::Item::setTexture(sf::Texture* _texture) {
    texture = _texture;
}

void UI::Item::addTexture(sf::Texture* _texture, UI::animationType type) {
    textures[type] = _texture;
}

UI::Item::~Item() {

}

void UI::Item::moveX(float range) {
    sprite.setPosition(sprite.getPosition().x + range, sprite.getPosition().y);
}

void UI::Item::moveY(float range) {
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + range);
}

void UI::Item::setRatio(float sizeXMax, float sizeYMax) {
    if ((sizeXMax / sprite.getScale().x) < (sizeYMax / sprite.getScale().y)) {
        sprite.setScale(sizeXMax / sprite.getScale().x, sizeXMax / sprite.getScale().x);
    } else {
        sprite.setScale(sizeYMax / sprite.getScale().y, sizeYMax / sprite.getScale().y);
    }
}

void UI::Item::setRatio(float ratio) {
    sprite.scale(ratio, ratio);
}

void UI::Item::setImage() {
    for (int i = 0; i < UI::animationType::ANIMATIONS_NUMBER; i++) {
        textures.push_back(texture);
    }
    sprite.setTexture(*texture);
}

void UI::Item::changeStatus(UI::animationType type) {
    UI::AItem::changeStatus(type);
    sprite.setTexture(*(textures[type]));
}
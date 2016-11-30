//
// Created by jonas_e on 11/26/16.
//

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "../../include/UI/Item.hh"

UI::Item::Item() : sprite() {
}

void UI::Item::setImage(std::string filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        sprite.setTexture(texture);
        std::cerr << "Failed to load : " << filename << std::endl; // essayer de charger un placeholder à la place
    }
}

void UI::Item::setPosition(unsigned int x, unsigned int y) {
    sprite.setPosition(x, y);
}

sf::Sprite UI::Item::getSprite() {
    return sprite;
}
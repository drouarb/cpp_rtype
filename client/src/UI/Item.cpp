//
// Created by jonas_e on 11/26/16.
//

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "../../include/UI/Item.hh"

UI::Item::Item() : sprite() {
}

void UI::Item::setImage(std::string filename) {
    name = filename;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load : " << filename << std::endl; // essayer de charger un placeholder à la place
    } else {
    sprite.setTexture(texture);
    }
}

void UI::Item::setPosition(unsigned int x, unsigned int y) {
    sprite.setPosition(x, y);
}

sf::Sprite UI::Item::getSprite() {
    //std::cerr << name << std::endl;
    //std::cerr << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
    return sprite;
}

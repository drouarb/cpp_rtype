//
// Created by jonas_e on 11/26/16.
//

#include <iostream>
#include "../../include/UI/Item.hh"

UI::Item::Item(itemType t) : AItem(t) {
    scale = 1;
    animationTick = 0;
    animation = new std::list<sf::Sprite*>{&sprite};
    for (int i = 0; i < UI::animationType::ANIMATIONS_NUMBER; i++) {
        animations.push_back(*animation);
    }
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
    px = x;
    py = y;
    sprite.setPosition(x, y);
}

sf::Sprite UI::Item::getSprite() {
    if (animated) {
        if (animationTick == 4) {
            animationTick = 0;
            animation->push_front(animation->back());
            animation->pop_back();
        }
        animationTick++;
        animation->front()->setPosition(px, py);
        return *animation->front();
    }
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
    //px += range;
    sprite.setPosition(sprite.getPosition().x + range, sprite.getPosition().y);
}

void UI::Item::moveY(float range) {
    //py += range;
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
    scale = ratio;
    if (animated)
        for (auto frame : animation[type])
            frame->setScale(ratio, ratio);
    sprite.scale(ratio, ratio);
}

void UI::Item::setImage() {
    for (int i = 0; i < UI::animationType::ANIMATIONS_NUMBER; i++) {
        textures.push_back(texture);
    }
    sprite.setTexture(*texture);
}

void UI::Item::addAnimation(UI::animationType animationType, short frames, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
    while (animations[animationType].size() > 0)
        animations[animationType].pop_back();
    for (int i = 0; i < frames; i++) {
        sf::Sprite *frame = new sf::Sprite();
        frame->setTexture(*texture);
        //std::cerr << "x: " << (i * width) + posX << " y:" << posY << " width:" << width << " height:" << height << " size:" << animations[animationType].size() << std::endl;
        frame->setTextureRect(sf::IntRect((i * width) + posX, posY, width, height));
        frame->setScale(scale, scale);
        animations[animationType].push_back(frame);
    }

    animated = true;
}

void UI::Item::addAnimation(UI::animationType animationType, short frames, unsigned int size) {
    while (animations[animationType].size() > 0)
        animations[animationType].pop_back();
    for (int i = 0; i < frames; i++) {
        sf::Sprite *frame = new sf::Sprite();
        frame->setTexture(*texture);
        //std::cerr << "x: " << (i * width) + posX << " y:" << posY << " width:" << width << " height:" << height << " size:" << animations[animationType].size() << std::endl;
        frame->setTextureRect(sf::IntRect((i * size) + 0, 0, size, size));
        frame->setScale(scale, scale);
        animations[animationType].push_back(frame);
    }
    animated = true;
}

void UI::Item::changeStatus(UI::animationType type) {
    UI::AItem::changeStatus(type);

    if (animated) {
        animation = &animations[type];
        //sprite.setTexture(*animation->front()->getTexture());
    }
    else
        sprite.setTexture(*(textures[type]));
    //std::cerr << "merde:" << animations[type].size() << std::endl;
}
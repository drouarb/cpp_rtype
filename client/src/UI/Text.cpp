//
// Created by jonas_e on 12/21/16.
//

#include <bitset>
#include "../../include/UI/Text.hh"

UI::Text::Text() : AItem(UI::TEXT) {
    initStatus = font.loadFromFile("media/font/Pixeled.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(10);
    text.setFillColor(sf::Color::White);
}

UI::Text::~Text() {

}

bool UI::Text::initOK() {
    return initStatus;
}

void UI::Text::setBackgroundColor(sf::Color color) {
      text.setOutlineColor(color);
}

void UI::Text::setString(const std::string &string) {
    text.setString(string);
}

void UI::Text::getString() {
    text.getString();
}

void UI::Text::setFont(const std::string &string) {
    font.loadFromFile(string);
}

void UI::Text::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void UI::Text::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

float UI::Text::getWidth() {
    return text.getGlobalBounds().width;
}

sf::Text *UI::Text::getText() {
    return &text;
}

void UI::Text::setImage(std::string filename) {

}

void UI::Text::setImage() {

}

void UI::Text::setRatio(float sizeXMax, float sizeYMax) {

}

void UI::Text::setRatio(float ratio) {

}

void UI::Text::changeStatus(UI::animationType type) {
    AItem::changeStatus(type);
}

void UI::Text::addAnimation(UI::animationType animationType, short frames, unsigned int size) {

}

void UI::Text::addAnimation(UI::animationType animationType, short frames, unsigned int posX, unsigned int posY,
                            unsigned int width, unsigned int height) {

}

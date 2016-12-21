//
// Created by jonas_e on 12/21/16.
//

#include <bitset>
#include "../../include/UI/Text.hh"

UI::Text::Text() {
    initStatus = font.loadFromFile("/home/jonas_e/Work/Epitech/rtype/media/font/Pixeled.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setOutlineColor(sf::Color::Red);
    text.setOutlineThickness(20);
    text.setFillColor(sf::Color::Green);
}

UI::Text::~Text() {

}

bool UI::Text::initOK() {
    return initStatus;
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

sf::Text *UI::Text::getText() {
    return &text;
}

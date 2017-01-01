//
// Created by jonas_e on 12/21/16.
//

#include <iostream>
#include "UI/MenuLayer.hh"

UI::Text* UI::MenuLayer::addTextBox(float x, float y) {
    textBoxes.push_back(new Text());
    if (!textBoxes.back()->initOK()) {
        throw(1);
    }
    textBoxes.back()->setPosition(x, y);
    return textBoxes.back();
}

void UI::MenuLayer::action() {
    for (auto textBox : textBoxes) {
        window->draw(*(textBox->getText()));
    }
}

UI::MenuLayer::MenuLayer() {

}

void UI::MenuLayer::init(sf::RenderWindow* win) {
    this->window = win;
}

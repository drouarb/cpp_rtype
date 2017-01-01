//
// Created by jonas_e on 12/27/16.
//

#include "UI/HUDLayer.hh"

UI::Text* UI::HUDLayer::addTextBox(float x, float y) {
    textBoxes.push_back(new Text());
    if (!textBoxes.back()->initOK()) {
        throw(1);
    }
    textBoxes.back()->setPosition(x, y);
    return textBoxes.back();
}

void UI::HUDLayer::action() {
    for (auto textBox : textBoxes) {
        window->draw(*(textBox->getText()));
    }
}

UI::HUDLayer::HUDLayer() {

}

void UI::HUDLayer::init(sf::RenderWindow* win) {
    this->window = win;
}
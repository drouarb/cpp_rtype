//
// Created by jonas_e on 12/17/16.
//

#include "../../include/UI/Background.hh"

UI::Background::Background() : Item(UI::BACKGROUND) {

}

UI::Background::~Background() {

}

float UI::Background::getSpeed() const {
    return speed;
}

void UI::Background::setSpeed(float speed) {
    Background::speed = -speed;
}

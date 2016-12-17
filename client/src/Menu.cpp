//
// Created by celeriy on 17/12/16.
//

#include <iostream>
#include "Menu.hh"

Menu::Menu() {

}

unsigned long Menu::getLayer_id() const {
    return layer_id;
}

void Menu::setLayer_id(unsigned long layed) {
    layer_id = layed;
}

const std::vector<UI::AItem *> &Menu::getListItem() const {
    return listItem;
}

void Menu::addButtons(UI::AItem *item) {
    listItem.push_back(item);
}

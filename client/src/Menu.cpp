//
// Created by celeriy on 17/12/16.
//

#include <iostream>
#include "Menu.hh"

using namespace client;
Menu::Menu() : current_selected(nullptr){
layer = nullptr;
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

void Menu::selectedNext() {
    for (int i = 0; listItem[i] ; i++)
    {
        if (listItem[i] == current_selected && i + 1 != listItem.size())
        {
            listItem[i]->changeStatus(UI::IDLE);
            listItem[i + 1]->changeStatus(UI::ACTIVE);
            current_selected = listItem[i + 1];
            break;
        }
    }
}

UI::AItem *Menu::getCurrent_selected() const {
    return current_selected;
}

void Menu::setCurrent_selected(UI::AItem *curret_selected) {
    current_selected = curret_selected;
}

void Menu::selectedPrev() {
    for (int i = 0; listItem[i] ; i++)
    {
        if (listItem[i] == current_selected && i - 1 != -1)
        {
            listItem[i]->changeStatus(UI::IDLE);
            listItem[i - 1]->changeStatus(UI::ACTIVE);
            current_selected = listItem[i - 1];
            break;
        }
    }
}

void Menu::putMenu() {
    layer->open();
}

void Menu::popMenu() {
    layer->close();
}

UI::ILayer *Menu::getLayer() const {
    return layer;
}

void Menu::setLayer(UI::ILayer *laye) {
    layer = laye;
}

const std::string &Menu::getName() const {
    return name;
}

void Menu::setName(const std::string &name) {
    Menu::name = name;
}

MenuType Menu::getType() const {
    return type;
}

void Menu::setType(MenuType type) {
    Menu::type = type;
}


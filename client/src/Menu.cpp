//
// Created by celeriy on 17/12/16.
//

#include <iostream>
#include "Menu.hh"

using namespace client;
Menu::Menu() : current_selected(nullptr){
layer = nullptr;
    default_selected = nullptr;
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

void Menu::addButtons(UI::AItem *item, ButtonsType type) {
    listItem.push_back(item);
    this->TypeMap[item] = type;
}

void Menu::selectedNext() {
    if (current_selected == nullptr)
        return;
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
    if (current_selected == nullptr)
        return;
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

 std::string Menu::getName() const {
    return name;
}

void Menu::setName(const std::string &name1) {
    name = name1;
}

MenuType Menu::getType() const {
    return type;
}

void Menu::setType(MenuType type) {
    Menu::type = type;
}

void Menu::addButtonsType(const std::string &menu, UI::AItem *item) {
    goToMap[item] = menu;
}

const std::string &Menu::getMenuName(UI::AItem *item) {
    return goToMap[item];
}

ButtonsType Menu::getType(UI::AItem *item) {
    return  this->TypeMap[item];
}

void Menu::setDefault_selected(UI::AItem *default_selected) {
    Menu::default_selected = default_selected;
}

void Menu::reloadCurrent() {
    if (default_selected != nullptr && default_selected != nullptr) {
        current_selected->changeStatus(UI::IDLE);
        current_selected = default_selected;
        current_selected->changeStatus(UI::ACTIVE);

    }
}

const std::string &Menu::getText() const {
    return text;
}

void Menu::setText(const std::string &text) {
    Menu::text = text;
}


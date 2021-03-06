//
// Created by celeriy on 17/12/16.
//

#include <iostream>
#include "Menu.hh"

using namespace client;

Menu::Menu() : current_selected(nullptr) {
    layer = nullptr;
    default_selected = nullptr;
    music = "";
    color = sf::Color(91, 91, 91);
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
    for (int i = 0; listItem[i]; i++) {
        if (listItem[i] == current_selected) {
            while (i + 1 != listItem.size()) {
                if (buttonsStats[listItem[i + 1]] == UNLOCK) {
                    if (textBox.find(current_selected) != textBox.end())
                        static_cast<UI::Text *>(current_selected)->setBackgroundColor(sf::Color::Black);
                    if (textBox.find(listItem[i + 1]) != textBox.end())
                            static_cast<UI::Text *>(listItem[i + 1])->setBackgroundColor(color);
                    current_selected->changeStatus(UI::IDLE);
                    listItem[i + 1]->changeStatus(UI::ACTIVE);
                    current_selected = listItem[i + 1];
                    break;
                }
                i++;
            }
            break;
        }
    }
}

UI::AItem *Menu::getCurrent_selected() const {
    return current_selected;
}

void Menu::setCurrent_selected(UI::AItem *curret_selected) {
    current_selected = curret_selected;
    if (textBox.find(current_selected) != textBox.end())
        static_cast<UI::Text *>(current_selected)->setBackgroundColor(color);
}

void Menu::selectedPrev() {
    if (current_selected == nullptr)
        return;
    for (int i = 0; listItem[i]; i++) {
        if (listItem[i] == current_selected) {
            while (i - 1 != -1) {
                if (buttonsStats[listItem[i - 1]] == UNLOCK) {
                    if (textBox.find(current_selected) != textBox.end())
                        static_cast<UI::Text *>(current_selected)->setBackgroundColor(sf::Color::Black);
                        if (textBox.find(listItem[i - 1]) != textBox.end())
                            static_cast<UI::Text *>(listItem[i - 1])->setBackgroundColor(color);

                    current_selected->changeStatus(UI::IDLE);
                    listItem[i - 1]->changeStatus(UI::ACTIVE);
                    current_selected = listItem[i - 1];
                    break;
                }
                i--;
            }
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
    return this->TypeMap[item];
}

void Menu::setDefault_selected(UI::AItem *default_selected) {
    Menu::default_selected = default_selected;
}

void Menu::reloadCurrent() {
    if (default_selected != nullptr && default_selected != nullptr) {
        current_selected->changeStatus(UI::IDLE);
        current_selected = default_selected;
        if (textBox.find(current_selected) != textBox.end())
                static_cast<UI::Text *>(current_selected)->setBackgroundColor(color);
        current_selected->changeStatus(UI::ACTIVE);

    }
}


const std::string &Menu::getText() const {
    return text;
}

void Menu::setText(const std::string &text) {
    Menu::text = text;
}

void Menu::setButtonsStats(UI::AItem *item, ButtonsStats type) {
    buttonsStats[item] = type;
}

void Menu::changeTextBox(UI::AItem *box, const std::string &c) {

    std::string res = "";
    if (textBox.find(box) != textBox.end())
        res = textBox[box];
    if (res.size() < 32)
        textBox[box] = res  + c;
    static_cast<UI::Text *>(box)->setString(textBox[box]);
}

void Menu::errasefromTextBox(UI::AItem *box) {
    std::string res = "";
    if (textBox.find(box) != textBox.end()) {
        if (textBox[box].size() > 0) {
            textBox[box].pop_back();
            static_cast<UI::Text *>(box)->setString(textBox[box]);
        }
    }
}

void Menu::addInfo(UI::AItem *item, int info) {
    this->SendInfo[item] = info;
}

int Menu::getInfo(UI::AItem *item) {
    return SendInfo[item];
}

const std::string &Menu::getTextFromtextBox(UI::AItem *item) {
    return textBox[item];
}

void Menu::erraseTextBox() {


    std::vector<UI::AItem*>vec;
    for (auto it =  listItem.begin(); it != listItem.end() ; it++) {
        if (TypeMap[*it] == TEXTBOX && buttonsStats[*it] == LOCK)
            vec.push_back(*it);
    }
    for (int i = 0; i != vec.size() ; i++)
    {
        textBox.erase(vec[i]);
        SendInfo.erase(vec[i]);
        buttonsStats.erase(vec[i]);
        static_cast<UI::Text*>(vec[i])->setString("");
    }
}

void Menu::addButtonsName(const std::string &name, UI::AItem *item) {
 ButtonsName[name] = item;
}

UI::AItem *Menu::getButtonsByName(const std::string &name) {
    if (ButtonsName.find(name) != ButtonsName.end())
        return ButtonsName[name];
    return nullptr;
}

void Menu::erraseTextFromTextBox(UI::AItem *item) {
    static_cast<UI::Text *>(item)->setString("");
}

void Menu::addTextToButtons(UI::AItem *item, const std::string &data) {
    textBox[item] = data;
}

void Menu::setMusic(const std::string &music) {
    Menu::music = music;
}

const std::string &Menu::getMusic() const {
    return music;
}


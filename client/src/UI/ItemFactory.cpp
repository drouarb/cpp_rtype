//
// Created by jonas_e on 11/25/16.
//

#include <UI/Button.hh>
#include "../../include/UI/ItemFactory.hh"

const std::map<UI::itemType , UI::ItemFactory::instantiateItem> UI::ItemFactory::itemMap = {
        {BUTTON, &instantiateButton},
        {ITEM, &instantiateNormalItem},
};


UI::ItemFactory::ItemFactory() {

}

UI::ItemFactory::~ItemFactory() {

}

UI::AItem* UI::ItemFactory::instantiateButton() {
    return /*new UI::Button()*/ nullptr;
}

UI::AItem* UI::ItemFactory::instantiateNormalItem() {
    return new UI::Item();
}

UI::AItem* UI::ItemFactory::instantiate(UI::itemType type) {
    return itemMap.at(type)();
}

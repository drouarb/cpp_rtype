//
// Created by jonas_e on 12/2/16.
//

#include <UI/Item.hh>
#include <iostream>
#include "../../include/UI/BackgroundLayer.hh"


UI::BackgroundLayer::BackgroundLayer() {
    items.push_back(itemFactory->instantiate(UI::BACKGROUND, ""));
    items.push_back(itemFactory->instantiate(UI::BACKGROUND, ""));

}

void    UI::BackgroundLayer::action() {
    if (backgroundDupplication->getSprite().getPosition().x == 0)
        backgroundOrigin->setPosition(static_cast<UI::Item*>(backgroundOrigin)->getSprite().getGlobalBounds().width, 0);
    if (backgroundOrigin->getSprite().getPosition().x == 0)
        backgroundDupplication->setPosition(static_cast<UI::Item*>(backgroundOrigin)->getSprite().getGlobalBounds().width, 0);
    for (auto item : items)
        static_cast<UI::Item*>(item)->moveX(static_cast<UI::Background*>(item)->getSpeed());
    //if bool est entrain de changer de fond ...
        // faire ça
    // déplacer les background
    // déplacer les objets
}

void    UI::BackgroundLayer::setBackground(UI::itemType type, const std::string &sprite) {
    AItem* item = itemFactory->instantiate(type, sprite);
    item->setImage();
    item->setPosition(0, 0);
    item->setRatio(1080 / static_cast<UI::Item*>(item)->getSprite().getGlobalBounds().height);
    backgroundOrigin = static_cast<UI::Background*>(item);
    backgroundOrigin->setSpeed(1);
    item = itemFactory->instantiate(type, sprite);
    item->setImage();
    item->setPosition(static_cast<UI::Item*>(item)->getSprite().getGlobalBounds().width, 0);
    item->setRatio(1080 / static_cast<UI::Item*>(item)->getSprite().getGlobalBounds().height);
    backgroundDupplication = static_cast<UI::Background*>(item);
    backgroundDupplication->setSpeed(1);
    delete(items[0]);
    delete(items[1]);
    items[0] = backgroundOrigin;
    items[1] = backgroundDupplication;
}

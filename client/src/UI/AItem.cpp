#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include "../../include/UI/AItem.hh"

void UI::AItem::playAnimation(animationType animationType) {
    sprites.at(animationType);
}

UI::AItem::AItem() {

}

UI::AItem::~AItem() {

}

/*static sf::Sprite UI::AItem::createSprite(const std::string filename, unsigned long part) {
    sf::Image image;
    std::vector<std::pair<unsigned int, sf::Sprite>*>* sfAnimation = new std::vector<std::pair<unsigned int, sf::Sprite>*>();
    if (image.loadFromFile(filename)) {
        unsigned int x = image.getSize().x;
        unsigned int y = image.getSize().y;
        for (int i = 0; i < part; i++) {
            sf::Sprite
            sfAnimation->push_back(new std::pair<unsigned int, sf::Sprite>(0, ));
        }
    }
}*/

void UI::AItem::addAnimation(UI::animationType animationType, Animation animation) {
    sprites.at(animationType) = animation;
}


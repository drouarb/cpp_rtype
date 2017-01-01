#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <UI/AItem.hh>

void UI::AItem::playAnimation(animationType animationType) {
    //sprites.at(animationType);
}

UI::AItem::AItem(itemType t) {
    type = t;
    status = UI::IDLE;
    animated = false;
    onetime = false;
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

void    UI::AItem::setID(uint32_t id) {
    this->id = id;
}

UI::itemType UI::AItem::getType() {
    return type;
}

uint32_t UI::AItem::getID() {
    return id;
}

void UI::AItem::changeStatus(UI::animationType type) {
    status = type;
}

void UI::AItem::finished() {
    onetime = true;
}
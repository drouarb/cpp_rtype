//
// Created by jonas_e on 11/25/16.
//

#ifndef CPP_RTYPE_BUTTON_HH
#define CPP_RTYPE_BUTTON_HH

#include "Item.hh"

namespace UI {
    class Button : public Item {
    public:
        Button();
        ~Button();
    private:
        std::vector<sf::Sprite> *sprites;
    };
}


#endif //CPP_RTYPE_BUTTON_HH

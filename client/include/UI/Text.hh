//
// Created by jonas_e on 12/21/16.
//

#include <UI/AItem.hh>
#include <SFML/Graphics/Text.hpp>

#ifndef CPP_RTYPE_TEXT_HH
#define CPP_RTYPE_TEXT_HH

namespace UI {
    class Text {
    private:
        sf::Text text;
        sf::Font font;
        bool initStatus;
    public:
        Text();
        ~Text();
        void setString (const std::string &string);
        void setFont (const std::string &string);
        void setCharacterSize (unsigned int size);
        sf::Text *getText();
        void getString();
        void setPosition(float x, float y);
        bool initOK();
    };
}

#endif //CPP_RTYPE_TEXT_HH

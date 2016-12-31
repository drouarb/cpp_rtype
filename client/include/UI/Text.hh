//
// Created by jonas_e on 12/21/16.
//

#include <UI/AItem.hh>
#include <SFML/Graphics/Text.hpp>

#ifndef CPP_RTYPE_TEXT_HH
#define CPP_RTYPE_TEXT_HH

namespace UI {
    class Text : public AItem {
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
        float getWidth();
        void setBackgroundColor(sf::Color color);

    private:
        void setImage(std::string filename);
        void setImage();
        void setRatio(float sizeXMax, float sizeYMax);
        void setRatio(float ratio);
        void changeStatus(animationType type);
        void addAnimation(UI::animationType animationType, short frames, unsigned int size);
        void addAnimation(UI::animationType animationType, short frames, unsigned int posX, unsigned int posY, unsigned int width,
                                  unsigned int height);
    };
}

#endif //CPP_RTYPE_TEXT_HH

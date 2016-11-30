#ifndef CPP_RTYPE_AITEM_HH
#define CPP_RTYPE_AITEM_HH

#include <map>
#include <vector>
#include <utility>
#include <string>
#define Animation std::vector<std::pair<unsigned int, std::string>> //std::string devrait etre remplacé par les parts d'image  (sf::Sprite) loadé

namespace UI {

    enum itemType {
        BUTTON,
        ITEM,
        ITEMS_NUMBER
    };

    enum animationType {
        IDLE,
        ACTIVE,
        ANIMATIONS_NUMBER
    };

    class AItem {
    public:
        AItem();
        ~AItem();

        virtual void setImage(std::string filename) = 0;
        virtual void setPosition(unsigned int posX, unsigned int posY) = 0;
        void addAnimation(UI::animationType animationType, Animation animation);
        void playAnimation(animationType animation);

    private:
        std::map<UI::animationType, Animation> sprites; //changer unsigned int dans un type plus générique ?


        //sf::Sprite createSprite(const std::string filename, unsigned long part);
    };
}


#endif //CPP_RTYPE_AITEM_HH

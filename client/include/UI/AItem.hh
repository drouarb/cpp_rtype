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
        ITEMS_NUMBER
    };

    enum animationType {
        IDLE,
        SIZE
    };

    class AItem {
    public:
        AItem();
        ~AItem();

        void addAnimation(UI::animationType animationType, Animation animation);
        void playAnimation(animationType animation);

    private:
        std::map<UI::animationType, Animation> sprite; //changer unsigned int dans un type plus générique ?
    };
}


#endif //CPP_RTYPE_AITEM_HH

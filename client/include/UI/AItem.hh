#ifndef CPP_RTYPE_AITEM_HH
#define CPP_RTYPE_AITEM_HH

#include <map>
#include <vector>
#include <utility>
#include <string>

namespace UI {

    enum itemType {
        BUTTON,
        ITEMS_NUMBER
    };

    class AItem {
    public:
        enum animation {
            IDLE,
            SIZE
        };
    private:
        std::map<UI::AItem::animation, std::vector<std::pair<unsigned int, std::string>>> sprite; //changer unsigned int dans un type plus générique ?
    };
}


#endif //CPP_RTYPE_AITEM_HH

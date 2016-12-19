//
// Created by jonas_e on 12/17/16.
//

#ifndef CPP_RTYPE_BACKGROUND_HH
#define CPP_RTYPE_BACKGROUND_HH

#include <UI/Item.hh>

namespace UI {
    class Background : public Item {
    public:
        Background();
        ~Background();
        float getSpeed() const;
        void setSpeed(float speed);
    private:
        float speed;
    };
}


#endif //CPP_RTYPE_BACKGROUND_HH

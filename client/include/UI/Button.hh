//
// Created by jonas_e on 11/25/16.
//

#ifndef CPP_RTYPE_BUTTON_HH
#define CPP_RTYPE_BUTTON_HH

#include "AItem.hh"

namespace UI {
    class Button : public AItem {
    public:
        Button();

        void onHover();
    };
}


#endif //CPP_RTYPE_BUTTON_HH

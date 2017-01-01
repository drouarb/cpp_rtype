//
// Created by jonas_e on 1/1/17.
//

#ifndef CPP_RTYPE_CREDITLAYER_HH
#define CPP_RTYPE_CREDITLAYER_HH

#include <SFML/System/Clock.hpp>
#include "ALayer.hh"
#include "UIManager.hh"

namespace UI {
    class Credit {
    public:
        Credit();
        ~Credit();
        void HereWeGo(UI::UIManager *ui);
    private:
        bool done;
    };
}


#endif //CPP_RTYPE_CREDITLAYER_HH

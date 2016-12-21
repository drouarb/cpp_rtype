//
// Created by celeriy on 17/12/16.
//

#ifndef CPP_RTYPE_AMENU_HH
#define CPP_RTYPE_AMENU_HH

#include <UI/ILayer.hh>
#include "UI/AItem.hh"

namespace client {
    enum MenuType : int
    {
        DEFAULT = 0,
        GAME = 1
    };
    class Menu {
    private:
        unsigned long layer_id;
        UI::ILayer *layer;
        std::string name;
        MenuType type;
        UI::AItem *current_selected;
    public:
        MenuType getType() const;

        void setType(MenuType type);

        const std::string &getName() const;

        void setName(const std::string &name);

        UI::ILayer *getLayer() const;

        void setLayer(UI::ILayer *layer);

    public:
        UI::AItem *getCurrent_selected() const;

        void setCurrent_selected(UI::AItem *current_selected);

    public:
        unsigned long getLayer_id() const;

        void setLayer_id(unsigned long layer_id);

        const std::vector<UI::AItem *> &getListItem() const;

        void addButtons(UI::AItem *);

    private:
        std::vector<UI::AItem *> listItem;
    public:
        Menu();

        ~Menu() {};

        void selectedNext();

        void selectedPrev();

        void putMenu();

        void popMenu();
    };
}


#endif //CPP_RTYPE_AMENU_HH

//
// Created by celeriy on 17/12/16.
//

#ifndef CPP_RTYPE_AMENU_HH
#define CPP_RTYPE_AMENU_HH

#include <UI/ILayer.hh>
#include "UI/AItem.hh"
class Menu {
private:
    unsigned  long layer_id;
    UI::ILayer *layer;
public:
    UI::ILayer *getLayer() const;

    void setLayer(UI::ILayer *layer);

private:
    UI::AItem *current_selected;
public:
    UI::AItem *getCurrent_selected() const;

    void setCurrent_selected(UI::AItem *current_selected);

public:
    unsigned long getLayer_id() const;

    void setLayer_id(unsigned long layer_id);

    const std::vector<UI::AItem *> &getListItem() const;

    void addButtons(UI::AItem *);

private:
    std::vector<UI::AItem*> listItem;
public:
    Menu();
    ~Menu(){};
    void selectedNext();
    void selectedPrev();
    void putMenu();
    void popMenu();
};


#endif //CPP_RTYPE_AMENU_HH

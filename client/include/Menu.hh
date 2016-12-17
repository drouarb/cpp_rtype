//
// Created by celeriy on 17/12/16.
//

#ifndef CPP_RTYPE_AMENU_HH
#define CPP_RTYPE_AMENU_HH

#include "UI/AItem.hh"
class Menu {
private:
    unsigned  long layer_id;
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

};


#endif //CPP_RTYPE_AMENU_HH

//
// Created by celeriy on 17/12/16.
//

#ifndef CPP_RTYPE_AMENU_HH
#define CPP_RTYPE_AMENU_HH

#include <UI/ILayer.hh>
#include <UI/Text.hh>
#include "UI/AItem.hh"

namespace client {
    enum MenuType : int
    {
        DEFAULT = 0,
        GAME = 1
    };
    enum ButtonsType : int
    {
        NONE = 0,
        GOTO  = 1,
        TEXTBOX = 2
    };
    enum ButtonsStats : int
    {
        LOCK = 0,
        UNLOCK = 1
    };
    class Menu {
    private:
        unsigned long layer_id;
        UI::ILayer *layer;
        std::string name;
        MenuType type;
        UI::AItem *default_selected;
        std::string text;
        std::map<UI::AItem*, ButtonsStats> buttonsStats;
        std::map<UI::AItem*, std::string> textBox;
        std::map<UI::AItem*, int>SendInfo;

    public:
        const std::string &getText() const;

        void setText(const std::string &text);

    public:
        void setDefault_selected(UI::AItem *default_selected);

    private:
        UI::AItem *current_selected;
        std::map<UI::AItem*, std::string>goToMap;
        std::map<UI::AItem*, ButtonsType> TypeMap;
    public:
        MenuType getType() const;

        void setType(MenuType type);

        std::string getName() const;

        void setName(const std::string &name);

        UI::ILayer *getLayer() const;

        void setLayer(UI::ILayer *layer);
        ButtonsType getType(UI::AItem *item);

    public:
        UI::AItem *getCurrent_selected() const;

        void setCurrent_selected(UI::AItem *current_selected);

    public:
        unsigned long getLayer_id() const;

        void setLayer_id(unsigned long layer_id);

        const std::vector<UI::AItem *> &getListItem() const;

        void addButtons(UI::AItem *, ButtonsType type);

        void addButtonsType(const std::string & menu, UI::AItem* item);

        const std::string &getMenuName(UI::AItem*);

        void setButtonsStats(UI::AItem *item, ButtonsStats type);

        void changeTextBox(UI::AItem *box, const std::string &c);

        void reloadCurrent();

        void errasefromTextBox(UI::AItem *box);

        void addInfo(UI::AItem *item, int info);

        int getInfo(UI::AItem *item);

        const  std::string &getTextFromtextBox(UI::AItem *item);

        void erraseTextBox();
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

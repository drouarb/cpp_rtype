/*
** trouve_b
*/

#ifndef GAMEUIINTERFACE_HH_
# define GAMEUIINTERFACE_HH_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <map>
#include "Definitions.hh"
#include "Entity.hh"
#include "IEventHandler.hh"
#include "UI/UIManager.hh"
#include "Menu.hh"

using namespace boost::property_tree;

namespace client {
    class GameUIInterface {
    private:
        std::map<typeide_t, std::string> typeEntity;
        std::vector<std::pair<uint8_t, uint16_t> > gameList;
        std::vector<std::pair<uint32_t, std::string> > leaderBoard;
        std::map<Entity*, UI::AItem *> gameItem;
        std::vector<Menu*> listMenu;
        UI::UIManager managerUi;
        UI::IWindow *window;
    private:
        GameUIInterface() {};
    public:
        GameUIInterface(IEventHandler *);

        ~GameUIInterface();

        void initUI();

        void displaySimple();

        typeide_t registerNewSprite(const std::string &);

        void feedLeaderBoard(std::vector<std::pair<uint32_t, std::string> > leaderBoard);

        void feedGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList);

        void addListEntity(std::vector<Entity *> listentity);

        void addEntity(Entity *listEntity);

        void updateListEntity();

        void updateEntity(Entity *entity);

        void deleteListEntity(std::vector<Entity *> listentity);

        void deleteEntity(Entity *entity);

        void addMenu(const std::string &path);
    private:
        typeide_t getNextId();
    };
}

#endif /*GAMEUIINTERFACE_HH_*/

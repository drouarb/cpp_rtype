/*
** trouve_b
*/

#ifndef GAMEUIINTERFACE_HH_
# define GAMEUIINTERFACE_HH_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <mutex>
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include "Definitions.hh"
#include "Entity.hh"
#include "IEventHandler.hh"
#include "UI/UIManager.hh"
#include "Menu.hh"
#include "TouchDefinition.hh"
#include "Information.hh"
using namespace boost::property_tree;

namespace client {
    class GameUIInterface {
    private:
        std::mutex *ui_mut;
        std::map<typeide_t, std::string> typeEntity;
        std::vector<std::pair<uint8_t, uint16_t> > gameList;
        std::vector<std::pair<uint32_t, std::string> > leaderBoard;
        std::map<Entity*, UI::AItem *> gameItem;
        std::vector<Menu*> listMenu;
        UI::UIManager managerUi;
        UI::IWindow *window;
        Menu *currentMenu;
        std::map<std::string ,client::Key>nav_map;
        static const std::map<sf::Keyboard::Key, client::Key> keymap;
    private:
        GameUIInterface() {};
    public:
        GameUIInterface(IEventHandler *, std::mutex *mut);

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

        void addNavMap(const std::string & path);

        s_info * manageInput(short key);

        std::string isNavKey(client::Key);

        void manageNavkey(const std::string &res);

        s_info * manageEnter();

        void changeMenu(const std::string & ne);

        void manageTouch(client::Key);

    private:
        typeide_t getNextId();
    };
}

#endif /*GAMEUIINTERFACE_HH_*/

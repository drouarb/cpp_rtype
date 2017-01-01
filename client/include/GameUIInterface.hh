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
#include "thread/Mutex.hh"
#include <SFML/Window/Keyboard.hpp>
#include "Definitions.hh"
#include "Entity.hh"
#include "IEventHandler.hh"
#include "UI/UIManager.hh"
#include "Menu.hh"
#include "TouchDefinition.hh"
#include "Information.hh"

#define CONF_FILE "config/configall.json"
#define CONF_NAV "config/navigation.json"

#define TICKRATEUI 60

namespace client {
    class GameUIInterface {
    private:
        Mutex* ui_mut;
        std::map<typeide_t, std::string> typeEntity;
        std::vector<std::pair<uint8_t, uint16_t> > gameList;
        std::vector<std::pair<uint32_t, std::string> > leaderBoard;
        std::map<Entity*, UI::AItem *> gameItem;
        std::vector<Menu*> listMenu;
        UI::UIManager managerUi;
        UI::IWindow *window;
        Menu *currentMenu;
        Entity* nplayer;
        UI::Text* playerHp;
        UI::AItem *playerSprite;
    private:
        std::map<std::string ,client::Key>nav_map;
        std::map<std::string , std::vector<int>>anim_map;
        static const std::map<sf::Keyboard::Key, client::Key> keymap;
        client::Key KeygameList;
		bool running;

    private:
        client::Key KeyLeaderBoard;
    private:
        GameUIInterface() {};
    public:
        GameUIInterface(IEventHandler *);

        ~GameUIInterface();

        void initUI();

        void displaySimple();

      void UILoop();

	  void stopUI();
      
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

        void addAnimaton(const std::string &path, UI::AItem *item);

        void addNavMap(const std::string & path);

        s_info * manageInput(short key);

        std::string isNavKey(client::Key);

        void manageNavkey(const std::string &res);

        s_info * manageEnter();

        void showError(const std::string &res);
        void changeMenu(const std::string & ne);

        void manageTouch(client::Key);

        void createStaticMenu();

        void reloadMenuRoomList();

        bool windowIsOpen();

        void setKeygameList(Key KeygameList);

        void setKeyLeaderBoard(Key KeyLeaderBoard);

        void setStringToButtons(const std::string &name, const std::string &data, const std::string &menuName);

        const std::string getStringFromButtons(const std::string &name, const std::string &menuName);

        void setNplayer(Entity *nplayer);

		void updateHp();

		void playSound(const std::string & path);

        void  addBackground(const std::string & path);
    private:
        typeide_t getNextId();

    };
}

#endif /*GAMEUIINTERFACE_HH_*/

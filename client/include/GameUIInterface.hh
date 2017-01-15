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

#define MUSIC_PATH "media/musics/"
#define MENU_PATH "media/menu/"
#define BLACK_BACKGROUND "media/menu/black-background.jpg"
#define BASIC_BACKGROUND "media/backgrounds/normal.png"
#define RTYPE_EX ".rtype"
#define AVATAR_EX "vatar.png"

namespace client
{
  class GameUIInterface
  {
  private:
    Mutex*							ui_mut;
    static const std::map<sf::Keyboard::Key, client::Key>	keymap;
    std::map<typeide_t, std::string>				typeEntity;
    std::map<std::string ,client::Key>				nav_map;
    std::map<std::string , std::vector<int> >			anim_map;
    std::map<Entity*, UI::AItem *>				gameItem;
    std::map<const std::string, int>				soundName;
    std::vector<std::pair<uint8_t, uint16_t> >			gameList;
    std::vector<std::pair<uint32_t, std::string> >		leaderBoard;
    std::vector<Menu*>						listMenu;
    std::vector<short>						pressedKey;
    UI::UIManager						managerUi;
    UI::IWindow							*window;
    UI::Text							*playerHp;
    UI::AItem							*playerSprite;
    client::Key							KeygameList;
    client::Key							KeyLeaderBoard;
    Menu							*currentMenu;
    Entity							*nplayer;
    bool							running;
    
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

    std::vector<s_info*> manageInput(client::Event event);

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

    void credit();

    void addSound(const std::string &sound);

    void playSoundEffect(const std::string &sound);
  private:
    typeide_t getNextId();

  };
}

#endif /*GAMEUIINTERFACE_HH_*/

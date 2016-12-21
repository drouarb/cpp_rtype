/*
** trouve_b
*/

#include <iostream>
#include <UI/BackgroundLayer.hh>
#include "GameUIInterface.hh"

using namespace client;

GameUIInterface::GameUIInterface(IEventHandler *handler, std::mutex *mut) {
    managerUi.init(1920, 1020);
    managerUi.getEventObserver()->setEventManager(handler);
    managerUi.getEventObserver()->listen(managerUi.getWindow(UI::MAIN_WINDOW));
    static_cast<UI::BackgroundLayer*>(managerUi.getWindow(UI::MAIN_WINDOW)->getLayer(UI::BACKGROUNDS))->setBackground(UI::BACKGROUND, "media/references/background.png");
     ui_mut = mut;
    currentMenu = nullptr;
    addNavMap("config/navigation.json");
}

GameUIInterface::~GameUIInterface() {
}

void GameUIInterface::initUI() {
    window = managerUi.getWindow(UI::MAIN_WINDOW);
    addMenu("config/menuStart.json");
    addMenu("config/menuConnection.json");
    currentMenu = listMenu[0];
}

void GameUIInterface::displaySimple() {
    window->display();
    managerUi.getEventObserver()->getEvent(); //TODO à modifier
}

typeide_t GameUIInterface::registerNewSprite(const std::string &str) {
    std::map<typeide_t, std::string>::iterator it;

    it = typeEntity.begin();
    while (it != typeEntity.end()) {
        if (it->second == str)
            return (it->first);
        ++it;
    }
    typeide_t newid = getNextId();
    typeEntity.insert(std::pair<typeide_t, std::string>(newid, str));
    return (newid);
}

void GameUIInterface::feedLeaderBoard(std::vector<std::pair<uint32_t, std::string> > nleaderBoard) {
    leaderBoard = nleaderBoard;
}

void GameUIInterface::feedGameList(std::vector<std::pair<uint8_t, uint16_t> > ngameList) {
    gameList = ngameList;
}


typeide_t GameUIInterface::getNextId() {
    static typeide_t id = 0;
    return (id++);
}

void GameUIInterface::addListEntity(std::vector<Entity *> listentity) {
    ui_mut->lock();
    for (int i = 0; listentity[i]; i++) {
        auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listentity[i]->getTypeid()],
                                                        listentity[i]->getPos().first, listentity[i]->getPos().second);
        gameItem[listentity[i]] = item;
    }
    ui_mut->unlock();
}

void GameUIInterface::addEntity(Entity *listEntity) {
    ui_mut->lock();

/*    int n = 0;
    int n1 = 0;

    std::string  final = typeEntity[listEntity->getId()];

    if (final.find(".gif") != std::string::npos) {
        final = final.replace(final.find(".gif"), 4, ".txt");
    }
    if (final.find(".png") != std::string::npos) {
        final = final.replace(final.find(".png"), 4, ".txt");
    }

    std::ifstream ifs = std::ifstream(final, std::ifstream::in);

    if (ifs.is_open()) {
        ifs >> n;
        ifs >> n1;
    }*/


    std::cout << "add entity  " << typeEntity[listEntity->getId()] << "pos_x  :" << listEntity->getPos().first  << "pos_y "  << listEntity->getPos().second<< std::endl ;
    auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listEntity->getTypeid()],
                                                    listEntity->getPos().first, listEntity->getPos().second);
    std::cerr << typeEntity[listEntity->getId()] <<"ici" << std::endl;

    if (typeEntity[listEntity->getId()].find("magical") != std::string::npos)
    {

        static_cast<UI::Item *>(item)->addAnimation(UI::IDLE, 4, 0, 0, 64, 64);
        item->changeStatus(UI::IDLE);
    }
    gameItem[listEntity] = item;
    ui_mut->unlock();
}

void GameUIInterface::updateListEntity() {
    ui_mut->lock();
    for (auto it = gameItem.begin(); it != gameItem.end(); it++) {
        it->second->setPosition(it->first->getPos().first, it->first->getPos().second);
    }
    ui_mut->unlock();
}

void GameUIInterface::updateEntity(Entity *entity) {
    ui_mut->lock();
    gameItem[entity]->setPosition(entity->getPos().first, entity->getPos().second);
    ui_mut->unlock();
}

void GameUIInterface::deleteListEntity(std::vector<Entity *> listentity) {
    ui_mut->lock();
    for (int i = 0; listentity[i]; i++) {
        window->deleteItem(gameItem[listentity[i]]);
        gameItem.erase(listentity[i]);
    }
    ui_mut->unlock();
}

void GameUIInterface::deleteEntity(Entity *entity) {
    ui_mut->lock();
    window->deleteItem(gameItem[entity]);
    gameItem.erase(entity);
    ui_mut->unlock();
}

void GameUIInterface::addMenu(const std::string &path) {
    ptree root;
    read_json(path, root);
    Menu *temp = new Menu;
    unsigned long id = window->addLayer(UI::MENU);
    temp->setLayer_id(id);
    temp->setName(root.get_child("Name").get_value<std::string>());
    temp->setType(static_cast<MenuType >(root.get_child("type").get_value<int>()));
    if (root.get_child("Default_Visibility").get_value<int>() == 0)
        window->getLayer(id)->open();
    else
        window->getLayer(id)->close();
    temp->setLayer(window->getLayer(id));
     int x = 0;
    int y = 0;
    int padding_up = root.get_child("padding_up").get_value<int>();
    int padding_left = root.get_child("padding_left").get_value<int>();
    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("Buttons")) {
                     BOOST_FOREACH(const ptree::value_type &child2,
                                  child.second.get_child("position")) {
                                    x = child2.second.get<int>("x");
                                    y = child2.second.get<int>("y");
                                }
                  auto item = window->getLayer(id)->addItem(UI::ITEM, "media/menu/" + child.second.get<std::string>("noselected"), x + padding_left , y + padding_up);
                    window->getLayer(id)->addTexture(item, UI::ACTIVE ,"media/menu/" + child.second.get<std::string>("selected"));
                    if (child.second.get<int>("default_selected") == 0)
                        item->changeStatus(UI::IDLE);
                    else {
                        temp->setDefault_selected(item);
                        temp->setCurrent_selected(item);
                        item->changeStatus(UI::ACTIVE);
                    }
                    temp->setButtonsStats(item, static_cast<ButtonsStats >(child.second.get<int>("lock")));
                    ButtonsType  typeB = static_cast<ButtonsType >(child.second.get<int>("type"));
                    if (typeB == GOTO)
                        temp->addButtonsType(child.second.get<std::string>("goto"), item);
                    temp->addButtons(item, typeB);
                }
    listMenu.push_back(temp);
}

void GameUIInterface::addNavMap(const std::string &path) {
    ptree root;
    read_json(path, root);
    nav_map["Next"] = static_cast<client::Key>(root.get_child("Next").get_value<int>());
    nav_map["Prev"] = static_cast<client::Key>(root.get_child("Prev").get_value<int>());
}

void GameUIInterface::manageInput(short key1) {

    std::string res;
    sf::Keyboard::Key key = static_cast<sf::Keyboard::Key >(key1);
    if (keymap.find(key) != keymap.end())
    {
        client::Key tmp = keymap.at(key);
        if (currentMenu->getType() == DEFAULT)
        {
            if (( res = isNavKey(tmp)) != "")
                manageNavkey(res);
            if (tmp == client::KEY_ENTER)
                manageEnter();
        }
    }
}

std::string GameUIInterface::isNavKey(client::Key key) {
    for (auto it  = nav_map.begin() ; it != nav_map.end(); it++)
    {
        if (it->second == key)
            return it->first;
    }
    return std::string("");
}

void GameUIInterface::manageNavkey(const std::string &res) {
    if (res == "Next")
        currentMenu->selectedNext();
    else
        currentMenu->selectedPrev();

}

void GameUIInterface::manageEnter() {

    if (currentMenu->getType(currentMenu->getCurrent_selected()) == GOTO)
    {
        changeMenu(currentMenu->getMenuName(currentMenu->getCurrent_selected()));
    }
}

void GameUIInterface::changeMenu(const std::string &ne) {
    for(int i = 0; listMenu[i]  ; i++)
    {
        if (listMenu[i]->getName() == ne)
        {
             currentMenu->popMenu();
            currentMenu->reloadCurrent();
            currentMenu = listMenu[i];
            currentMenu->putMenu();
            break;
        }
    }
}

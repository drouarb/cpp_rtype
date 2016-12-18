/*
** trouve_b
*/

#include <iostream>
#include "GameUIInterface.hh"

using namespace client;

GameUIInterface::GameUIInterface(IEventHandler *handler, std::mutex *mut) {
    managerUi.init(1920, 1020);
    managerUi.getEventObserver()->setEventManager(handler);
    managerUi.getEventObserver()->listen(managerUi.getWindow(UI::MAIN_WINDOW));
    ui_mut = mut;

}

GameUIInterface::~GameUIInterface() {
}

void GameUIInterface::initUI() {
    window = managerUi.getWindow(UI::MAIN_WINDOW);
   // addMenu("config/menuStart.json");
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
    auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listEntity->getTypeid()],
                                                    listEntity->getPos().first, listEntity->getPos().second);
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
    if (root.get_child("Default_Visibility").get_value<int>() == 0)
        window->getLayer(id)->open();
    else
        window->getLayer(id)->close();
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
                        temp->setCurrent_selected(item);
                        item->changeStatus(UI::ACTIVE);
                    }
                        temp->addButtons(item);
                }
    listMenu.push_back(temp);
}

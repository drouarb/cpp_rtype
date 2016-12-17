/*
** trouve_b
*/

#include <iostream>
#include "GameUIInterface.hh"

using namespace client;

GameUIInterface::GameUIInterface(IEventHandler *handler) {
    managerUi.init(1920, 1020);
    managerUi.getEventObserver()->setEventManager(handler);
    managerUi.getEventObserver()->listen(managerUi.getWindow(UI::MAIN_WINDOW));
}

GameUIInterface::~GameUIInterface() {
}

void GameUIInterface::initUI() {
    window = managerUi.getWindow(UI::MAIN_WINDOW);
    addMenu("config/menuTest.json");
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
    for (int i = 0; listentity[i]; i++) {
        auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listentity[i]->getTypeid()],
                                                        listentity[i]->getPos().first, listentity[i]->getPos().second);
        gameItem[listentity[i]] = item;
    }
}

void GameUIInterface::addEntity(Entity *listEntity) {
    auto item = window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listEntity->getTypeid()],
                                                    listEntity->getPos().first, listEntity->getPos().second);
    gameItem[listEntity] = item;
}

void GameUIInterface::updateListEntity() {
    for (auto it = gameItem.begin(); it != gameItem.end(); it++) {
        it->second->setPosition(it->first->getPos().first, it->first->getPos().second);
    }
}

void GameUIInterface::updateEntity(Entity *entity) {
    gameItem[entity]->setPosition(entity->getPos().first, entity->getPos().second);
}

void GameUIInterface::deleteListEntity(std::vector<Entity *> listentity) {
    for (int i = 0; listentity[i]; i++) {
        window->deleteItem(gameItem[listentity[i]]);
        gameItem.erase(listentity[i]);
    }
}

void GameUIInterface::deleteEntity(Entity *entity) {
    window->deleteItem(gameItem[entity]);
    gameItem.erase(entity);
}

void GameUIInterface::addMenu(const std::string &path) {
    ptree root;
    read_json(path, root);
    Menu *temp = new Menu;
    std::cout << root.get_child("Name").get_value<std::string>() << std::endl;
    unsigned long id = window->addLayer(UI::MENU);
    temp->setLayer_id(id);
    std::cout << root.get_child("Default_Visibility").get_value<int>() << std::endl;
    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("Buttons")) {
                    std::cout << child.second.get<std::string>("selected") << std::endl;
                    std::cout << child.second.get<std::string>("noselected") << std::endl;
                    std::cout << child.second.get<int>("default_selected") << std::endl;
                    BOOST_FOREACH(const ptree::value_type &child2,
                                  child.second.get_child("position")) {
                                    std::cout << child2.second.get<int>("x") << std::endl;
                                    std::cout << child2.second.get<int>("y") << std::endl;
                                }
                }
}

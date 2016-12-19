//
// Created by jonas_e on 12/2/16.
//

#include <EventManager.hh>


void client::EventManager::onKeyPressed(short key) {
event = key;
}

client::EventManager::EventManager(client::GameClient *gameclient)  : gameClient(gameclient), event(-42){

}

client::EventManager::~EventManager() {

}

void client::EventManager::onMouseRealease(short x, short y) {

}

void client::EventManager::onKeyRealease(short key) {
event = -42;
}

short client::EventManager::getEvent() {
short buff = 0;
    if (event != -42)
    {
        buff = event;
        event = -42;
    }
    else
        buff = event;
    return (buff);

}

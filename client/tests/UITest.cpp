#include <UI/UIManager.hh>
#include <UI/UIManager.cpp>
#include <UI/Window.cpp>
#include <UI/LayerFactory.cpp>
#include <UI/Item.cpp>
#include <UI/AItem.cpp>
#include <UI/ItemFactory.cpp>
#include <UI/AudioManager.cpp>
#include <UI/GameLayer.cpp>
#include <UI/ALayer.cpp>
#include <iostream>
#include <stdlib.h>
#include <UI/EventObserver.cpp>
#include <EventManager.cpp>


int testshitfunction(int modifier, UI::UIManager *neue) {
    static UI::UIManager *ui = NULL;
    if (neue) {
        ui = neue;
    } else {
    ui->getAudioManager()->setVolume(ui->getAudioManager()->getVolume() + modifier);
    }
    return 1;
}

int main()
{
    UI::UIManager *ui = new UI::UIManager();
    UI::AItem* item;
    UI::AItem* item2;

    ui->init();
    ui->getEventObserver()->listen(ui->getWindow(UI::MAIN_WINDOW));

    ui->getAudioManager()->playMusic("/home/jonas_e/Work/Epitech/rtype/media/musics/Lady_Crimson.ogg");
    ui->getAudioManager()->setVolume(ui->getAudioManager()->getVolume() - 95); // plus et ça fait mal aux oreilles sur arch avec un alsa + ganoox à
    item = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->addItem(UI::ITEM, "/home/jonas_e/Desktop/ALL_GONE.jpg", 250, 250);
    item2 = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::BACKGROUNDS)->addItem(UI::ITEM, "/home/jonas_e/Desktop/fire.png", 300, 300);
    UI::IWindow* window = ui->getWindow(UI::MAIN_WINDOW);
    UI::IEventObserver* eventObserver = ui->getEventObserver();
    item2->setRatio(0.20);
    testshitfunction(0, ui);
    while (window->isOpen()) {
        window->display();
        if (ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->isVisible())
            ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->close();
        else
            ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->open();
        item->setPosition(100, 100);
        eventObserver->getEvent();
    }
    return 1;
}
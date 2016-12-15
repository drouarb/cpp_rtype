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

    /* TEST BASIC SANS ABSTRACTION ********************
    sf::RenderWindow* app = new sf::RenderWindow(sf::VideoMode(800,600,32), "mdr");
    sf::Texture texture;
    sf::Sprite sprite;


    if (!texture.loadFromFile("/home/jonas_e/Desktop/ALL_GONE.jpg"))
    {
        std::cout<<"Erreur durant le chargement de l'image"<<std::endl;
        return 0; // On ferme le programme
    }
    else // Si le chargement de l'image a réussi
    {
        sprite.setTexture(texture);
    }
    sprite.setPosition(250,250);
    while (app->isOpen()) {
        app->draw(sprite);
        app->display();
    }*/

    /* TEST CLASSIQUE SANS ABSTRACTION *********************/

    unsigned long item;
   std::string filename("/home/jonas_e/Desktop/ALL_GONE.jpg");
//    sf::Sprite sprite; //peut �tre une partie d'image

    ui->init(800, 600);
        ui->getEventObserver()->listen(ui->getWindow(UI::MAIN_WINDOW));
        //layer = ui->getWindow(UI::MAIN_WINDOW)->addLayer(UI::GAME);
        ui->getAudioManager()->playMusic("/home/jonas_e/Work/Epitech/rtype/media/musics/Lady_Crimson.ogg");
        ui->getAudioManager()->setVolume(ui->getAudioManager()->getVolume() - 95); // plus et ça fait mal aux oreilles sur arch avec un alsa + ganoox à
        item = ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->addItem(UI::ITEM, "/home/jonas_e/Desktop/ALL_GONE.jpg", 250, 250);
        ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->setImage("/home/jonas_e/Desktop/ALL_GONE.jpg");
        ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->setPosition(250, 250);
        //ui->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->addAnimation(UI::IDLE, std::vector<std::pair<unsigned int, std::string> {0, "/home/jonas_e/Desktop/ALL_GONE.jpg"}>);
        UI::IWindow* window = ui->getWindow(UI::MAIN_WINDOW);
        UI::IEventObserver* eventObserver = ui->getEventObserver();
        testshitfunction(0, ui);
        while (window->isOpen()) {
            window->display();
            eventObserver->getEvent();
            //vs
            //ui->display();

        }
    return 1;
}
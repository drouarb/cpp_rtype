#include <UI/UIManager.hh>
#include <UI/UIManager.cpp>
#include <UI/Window.cpp>
#include <UI/LayerFactory.cpp>
#include <UI/ItemFactory.cpp>
#include <UI/AudioManager.cpp>
#include <iostream>


int main()
{
    UI::UIManager *ui = new UI::UIManager();
    unsigned long layer;
    sf::Image image;
    std::string filename("/home/jonas_e/Desktop/ALL_GONE.jpg");
    sf::Sprite sprite; //peut �tre une partie d'image

    if (image.loadFromFile("/home/jonas_e/Desktop/ALL_GONE.jpg")) {
        ui->init();
        //layer = ui->getWindow(UI::MAIN_WINDOW)->addLayer(UI::GAME);
        ui->addItemToLayer(UI::BUTTON, "/home/jonas_e/Desktop/ALL_GONE.jpg", 250, 250, UI::GAME);
        ui->getAudioManager()->playMusic("/home/jonas_e/Work/Epitech/rtype/media/musics/Lady_Crimson.ogg");
        ui->getAudioManager()->setVolume(ui->getAudioManager()->getVolume() - 95); // plus et ça fait mal aux oreilles sur arch avec un alsa + ganoox à
        while (ui->getWindow(UI::MAIN_WINDOW)->isOpen()) {
            ui->getWindow(UI::MAIN_WINDOW)->display();
        }
    }
    else {
        std::cerr << "failed to load: " << filename << std::endl;
    }

    return 1;
}
#include <UI/UIManager.hh>
#include <UI/UIManager.cpp>
#include <UI/Window.cpp>
#include <UI/LayerFactory.cpp>
#include <UI/ItemFactory.cpp>


int main()
{
    UI::UIManager *ui = new UI::UIManager();
    unsigned long layer;

    ui->init();
    //layer = ui->getWindow(UI::MAIN_WINDOW)->addLayer(UI::GAME);
    ui->addItemToLayer(UI::BUTTON, "/home/jonas_e/Desktop/ALL_GONE.jpg", 250, 250, UI::GAME);
    while (ui->getWindow(UI::MAIN_WINDOW)->isOpen()) {
        ui->getWindow(UI::MAIN_WINDOW)->display();
    }
    return 1;
}
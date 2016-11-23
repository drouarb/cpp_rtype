#include <UI/UIManager.hh>
#include <UI/UIManager.cpp>
#include <UI/Window.cpp>


int main()
{
    UI::UIManager *ui = new UI::UIManager();
    ui->init();
    while (ui->getWindow(UI::MAIN_WINDOW)->isOpen()) {
        ui->getWindow(UI::MAIN_WINDOW)->display();
    }
    return 1;
}
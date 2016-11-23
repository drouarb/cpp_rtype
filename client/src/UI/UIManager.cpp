
#include <UI/UIManager.hh>
#include <UI/Window.hh>

UI::UIManager::UIManager() {

}

UI::UIManager::~UIManager() {
    for (auto window : windows) {
        delete (window);
    }
}

void UI::UIManager::init() {
    IWindow* mainWindow = new UI::Window();
    mainWindow->setName("rtype");
    mainWindow->setSize(800, 600);
    mainWindow->render();
    windows.push_back(mainWindow);
}

UI::IWindow *UI::UIManager::getWindow(UI::windowType windowType) {
    return windows[windowType];
}

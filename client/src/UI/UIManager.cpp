
#include <UI/UIManager.hh>
#include <UI/Window.hh>
#include <UI/AudioManager.hh>

UI::UIManager::UIManager() {
    audioManager = new UI::AudioManager();
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
    windows[MAIN_WINDOW]->addLayer(MENU);
    windows[MAIN_WINDOW]->addLayer(HUD);
    windows[MAIN_WINDOW]->addLayer(GAME);
    windows[MAIN_WINDOW]->addLayer(BACKGROUND);
}

UI::IWindow *UI::UIManager::getWindow(UI::windowType windowType) {
    return windows[windowType];
}

unsigned long UI::UIManager::addItemToLayer(UI::itemType type, std::string sprite, int posX, int posY, unsigned long LayerID) {
    return 0;
}

int UI::UIManager::UpdateItem(unsigned long layerID, unsigned long itemID) {

}

int UI::UIManager::addItemToGame(UI::itemType type, std::string sprite, int posX, int posY) {
    return 0;
}

int UI::UIManager::addLayer(UI::layerType layerType, UI::windowType windowType) {
    return windows[windowType]->addLayer(layerType); // on verra, certainement pas utile.
}

UI::IAudioManager *UI::UIManager::getAudioManager() {
    return audioManager;
}

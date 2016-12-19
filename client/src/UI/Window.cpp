#include <UI/Window.hh>
#include <UI/Item.hh>
#include <iostream>
#include <algorithm>


UI::Window::Window() {
    layerFactory = new LayerFactory();
    length = 800;
    width = 600;
    name = "rtype";
    window = new sf::RenderWindow(sf::VideoMode(length, width, 32), name);
}

UI::Window::~Window() {
    window->close();
    delete(window);
    delete(layerFactory);
}

void UI::Window::setSize(unsigned int length, unsigned int width) {
    this->length = length;
    this->width = width;
}

void UI::Window::setName(std::string name) {
    this->name = name;
}

void UI::Window::render() {
    window->create(sf::VideoMode(length, width, 32), name);
    window->setFramerateLimit(60);
    //std::cerr << "DEBUGplskill: " << window->getPosition().x << std::endl;
}

bool UI::Window::isOpen() {
    return window->isOpen();
}

void UI::Window::display() {
    window->clear();
    for (auto layer : layers) {
        if (layer->isVisible()) {
            layer->action();
            for (auto item : layer->getItems()) {
                //std::cerr << "Debug: " << (static_cast<Item*>(item)->getSprite()).getPosition().x << std::endl;
                window->draw(static_cast<Item*>(item)->getSprite());
            }
        }
    }
    window->display();
    //std::cerr << "DEBUGplskill: " << window->getPosition().x << std::endl;
}

unsigned long UI::Window::addLayer(UI::layerType layer) {
    layers.push_back(layerFactory->instantiate(layer));
    return layers.size() - 1;
}

UI::ILayer *UI::Window::getLayer(unsigned long layer) {
    return layers[layer];
}

sf::RenderWindow *UI::Window::getWindow() {
    return window;
}

void UI::Window::deleteItem(AItem* item) {
    for (auto layer : layers) {
        auto iterator = std::find(layer->getItems().begin(), layer->getItems().end(), item);
        if (iterator != layer->getItems().end()) {
            layer->getItems().erase(iterator);
            delete(item);
            return;
        }
    }
}

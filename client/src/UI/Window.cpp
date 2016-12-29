#include <UI/Window.hh>
#include <UI/Item.hh>
#include <iostream>
#include <algorithm>
#include <UI/MenuLayer.hh>


UI::Window::Window() {
    layerFactory = new LayerFactory();
    length = LENGTH;
    width = WIDTH;
    name = "rtype";
    window = new sf::RenderWindow(sf::VideoMode(length, width, 32), name);
    alertText.setPosition(0, 0);
    alertText.setString("");
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
    if (alerted) {
        if (alertClock.getElapsedTime().asSeconds() > 10) {
            alerted = false;
            alertText.setString("");
        }
        window->draw(*alertText.getText());
    }
    window->display();
    //std::cerr << "DEBUGplskill: " << window->getPosition().x << std::endl;
}

unsigned long UI::Window::addLayer(UI::layerType layer) {
    layers.push_back(layerFactory->instantiate(layer));
    if (layer == MENU) {
        static_cast<UI::MenuLayer*>(layers.back())->init(window);
    }
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

void UI::Window::alert(const std::string &string) {
    alertText.setString(string);
    alerted = true;
    alertClock.restart();
}

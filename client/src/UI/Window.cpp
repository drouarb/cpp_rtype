#include <UI/Window.hh>
#include <UI/Item.hh>
#include <iostream>


UI::Window::Window() {
    layerFactory = new LayerFactory();
    length = 800;
    width = 600;
    name = "rtype";
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
    window = new sf::RenderWindow(sf::VideoMode(length, width), name);
}

bool UI::Window::isOpen() {
    return window->isOpen();
}

void UI::Window::display() {
    /*for (auto layer : layers) {
        for (auto item : layer->getItems()) {
            //std::cerr << "Debug: " << (static_cast<Item*>(item)->getSprite()).getPosition().x << std::endl;
            window->draw(static_cast<Item*>(item)->getSprite());
        }
    }*/
    window->display();
}

unsigned long UI::Window::addLayer(UI::layerType layer) {
    layers.push_back(layerFactory->instantiate(layer));
    return layers.size() - 1;
}

UI::ILayer *UI::Window::getLayer(UI::layerType layer) {
    return layers[layer];
}

#include <UI/Window.hh>


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
    window->display();
}

unsigned long UI::Window::addLayer(UI::layerType layer) {
    layers.push_back(layerFactory->instantiate(layer));
    return layers.size();
}
#include <UI/Window.hh>


UI::Window::Window() {
    length = 800;
    width = 600;
    name = "rtype";
}

UI::Window::~Window() {
    window->close();
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

void UI::Window::addLayer(ILayer* layer) { //remplacer layer par Template à layer genre enum
    layers.push_back(layer);
}
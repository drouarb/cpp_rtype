#include <iostream>
#include <EventManager.hh>
#include "../../include/UI/EventObserver.hh"

UI::EventObserver::EventObserver() {

}

void UI::EventObserver::getEvent() {
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                client::EventManager::onKeyPressed(event.key.code);
                break;
            case sf::Event::KeyReleased:break;
            case sf::Event::MouseButtonPressed:event.mouseButton.x;event.mouseButton.y;
            case sf::Event::MouseButtonReleased:event.mouseButton.x;event.mouseButton.y;
            case sf::Event::MouseMoved:event.mouseButton.x;event.mouseButton.y;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128){
                    //std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                }
            default:
                break;
/*
            case sf::Event::Resized:break;
            case sf::Event::LostFocus:break;
            case sf::Event::GainedFocus:break;
            case sf::Event::MouseWheelMoved:break;
            case sf::Event::MouseWheelScrolled:break;
            case sf::Event::MouseEntered:break;
            case sf::Event::MouseLeft:break;
            case sf::Event::JoystickButtonPressed:break;
            case sf::Event::JoystickButtonReleased:break;
            case sf::Event::JoystickMoved:break;
            case sf::Event::JoystickConnected:break;
            case sf::Event::JoystickDisconnected:break;
            case sf::Event::TouchBegan:break;
            case sf::Event::TouchMoved:break;
            case sf::Event::TouchEnded:break;
            case sf::Event::SensorChanged:break;
            case sf::Event::Count:break;
*/
            case sf::Event::Resized:break;
            case sf::Event::LostFocus:break;
            case sf::Event::GainedFocus:break;
            case sf::Event::MouseWheelMoved:break;
            case sf::Event::MouseWheelScrolled:break;
            case sf::Event::MouseEntered:break;
            case sf::Event::MouseLeft:break;
            case sf::Event::JoystickButtonPressed:break;
            case sf::Event::JoystickButtonReleased:break;
            case sf::Event::JoystickMoved:break;
            case sf::Event::JoystickConnected:break;
            case sf::Event::JoystickDisconnected:break;
            case sf::Event::TouchBegan:break;
            case sf::Event::TouchMoved:break;
            case sf::Event::TouchEnded:break;
            case sf::Event::SensorChanged:break;
            case sf::Event::Count:break;
        }
    }
}

void UI::EventObserver::init(sf::RenderWindow* win) {
    window = win;
}

void UI::EventObserver::listen(UI::IWindow *win) {
    window = static_cast<UI::Window*>(win)->getWindow();
}

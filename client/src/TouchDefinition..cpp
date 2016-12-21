//
// Created by celeriy on 21/12/16.
//

#include "TouchDefinition.hh"
#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <GameUIInterface.hh>

const std::map<sf::Keyboard::Key, client::Key> client::GameUIInterface::keymap = {
        {sf::Keyboard::Key::Up,        client::KEY_UP},
        {sf::Keyboard::Key::Down,      client::KEY_DOWN},
        {sf::Keyboard::Key::Right,     client::KEY_RIGHT},
        {sf::Keyboard::Key::Left,      client::KEY_LEFT},
        {sf::Keyboard::Key::Space,     client::KEY_SPACE},
        {sf::Keyboard::Key::Escape,     client::KEY_ESCAPE},
        {sf::Keyboard::Key::A,         client::KEY_A},
        {sf::Keyboard::Key::B,         client::KEY_B},
        {sf::Keyboard::Key::C,         client::KEY_C},
        {sf::Keyboard::Key::D,         client::KEY_D},
        {sf::Keyboard::Key::E,         client::KEY_E},
        {sf::Keyboard::Key::F,         client::KEY_F},
        {sf::Keyboard::Key::Return,    client::KEY_ENTER},
        {sf::Keyboard::Key::G,         client::KEY_G},
        {sf::Keyboard::Key::H,         client::KEY_H},
        {sf::Keyboard::Key::I,         client::KEY_I},
        {sf::Keyboard::Key::J,         client::KEY_J},
        {sf::Keyboard::Key::K,         client::KEY_K},
        {sf::Keyboard::Key::L,         client::KEY_L},
        {sf::Keyboard::Key::M,         client::KEY_M},
        {sf::Keyboard::Key::N,         client::KEY_N},
        {sf::Keyboard::Key::O,         client::KEY_O},
        {sf::Keyboard::Key::P,         client::KEY_P},
        {sf::Keyboard::Key::Q,         client::KEY_Q},
        {sf::Keyboard::Key::R,         client::KEY_R},
        {sf::Keyboard::Key::S,         client::KEY_S},
        {sf::Keyboard::Key::T,         client::KEY_T},
        {sf::Keyboard::Key::U,         client::KEY_U},
        {sf::Keyboard::Key::V,         client::KEY_V},
        {sf::Keyboard::Key::W,         client::KEY_W},
        {sf::Keyboard::Key::X,         client::KEY_X},
        {sf::Keyboard::Key::Y,         client::KEY_Y},
        {sf::Keyboard::Key::Z,         client::KEY_Z},
        {sf::Keyboard::Key::Num0,         client::KEY_0},
        {sf::Keyboard::Key::Num1,         client::KEY_1},
        {sf::Keyboard::Key::Num2,         client::KEY_2},
        {sf::Keyboard::Key::Num3,         client::KEY_3},
        {sf::Keyboard::Key::Num4,         client::KEY_4},
        {sf::Keyboard::Key::Num5,         client::KEY_5},
        {sf::Keyboard::Key::Num6,         client::KEY_6},
        {sf::Keyboard::Key::Num7,         client::KEY_7},
        {sf::Keyboard::Key::Num8,         client::KEY_8},
        {sf::Keyboard::Key::Num9,         client::KEY_9},

        {sf::Keyboard::Key::Numpad0,   client::KEY_0},
        {sf::Keyboard::Key::Numpad1,   client::KEY_1},
        {sf::Keyboard::Key::Numpad2,   client::KEY_2},
        {sf::Keyboard::Key::Numpad3,   client::KEY_3},
        {sf::Keyboard::Key::Numpad4,   client::KEY_4},
        {sf::Keyboard::Key::Numpad5,   client::KEY_5},
        {sf::Keyboard::Key::Numpad6,   client::KEY_6},
        {sf::Keyboard::Key::Numpad7,   client::KEY_7},
        {sf::Keyboard::Key::Numpad8,   client::KEY_8},
        {sf::Keyboard::Key::Numpad9,   client::KEY_9}

};
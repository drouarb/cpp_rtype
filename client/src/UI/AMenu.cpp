//
// Created by celeriy on 17/12/16.
//

#include "AMenu.hh"

AMenu::AMenu(const std::string &path) {
        read_json(path, root);
}

//
// Created by celeriy on 17/12/16.
//

#include <iostream>
#include "AMenu.hh"

AMenu::AMenu(const std::string &path) {
    read_json(path, root);

    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("Buttons")) {
                    std::cout << child.second.get<std::string>("buttons_name") << std::endl;
                }
}

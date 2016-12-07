
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include "boost/property_tree/json_parser.hpp"
#include "Level.hh"

server::Level::Level(const std::string &filepath) {
    // Create a root
    boost::property_tree::ptree root;

    // Load the json file in this ptree
    boost::property_tree::json_parser::read_json(filepath, root);


    this->name = root.get_child("name").get_value<std::string>();

    BOOST_FOREACH(boost::property_tree::ptree::value_type
                          child, root.get_child("spawns")) {

                    Spawn spawn;
                    spawn.dlName = child.second.get_child("dlName").get_value<std::string>();
                    spawn.time = child.second.get_child("time").get_value<round_t>();
                    spawn.posX = child.second.get_child("posX").get_value<pos_t>();
                    spawn.posY = child.second.get_child("posY").get_value<pos_t>();

                    this->spawns[spawn.time].push_back(spawn);
                }
}

server::Level::~Level() {}

const std::vector<server::Spawn> &server::Level::getNewSpawns(server::round_t tick) const {
    return this->spawns[tick];
}

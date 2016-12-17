//
// Created by celeriy on 17/12/16.
//

#ifndef CPP_RTYPE_AMENU_HH
#define CPP_RTYPE_AMENU_HH

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
using namespace boost::property_tree;
class AMenu {
protected:
    ptree root;
public:
    AMenu(const std::string & path);
    virtual ~AMenu(){};
};


#endif //CPP_RTYPE_AMENU_HH

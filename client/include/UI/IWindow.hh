#ifndef CPP_RTYPE_IWINDOW_HH_
#define CPP_RTYPE_IWINDOW_HH_

#include <string>

namespace UI {
    class IWindow {
    public:
        virtual ~IWindow(){};
        virtual void setSize(unsigned int length, unsigned int width) = 0;
        virtual void setName(std::string windowName) = 0;
        virtual void render() = 0;
        virtual bool isOpen() = 0;
        virtual void display() = 0;
    };
}

#endif //CPP_RTYPE_IWINDOW_HH_
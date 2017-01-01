#ifndef CPP_RTYPE_EVENTOBSERVER_HH
#define CPP_RTYPE_EVENTOBSERVER_HH


#include "IEventObserver.hh"
#include "Window.hh"

namespace UI {
    class EventObserver : public IEventObserver {
    public:
        EventObserver();
        void init(sf::RenderWindow* window);
        void listen(UI::IWindow *window);
        void getEvent();
        bool received();
        void setEventManager(client::IEventHandler *eventHandler);
    private:
        sf::RenderWindow* window;
        sf::Event event;
        client::IEventHandler *eventManager;
    };
}


#endif //CPP_RTYPE_EVENTOBSERVER_HH

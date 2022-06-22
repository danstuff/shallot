#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "global.h"
#include "page.h"
#include "ruler.h"

class Controller : public Gtk::ScrolledWindow {
    public:
        Gtk::Box layout;

        Ruler ruler;
        
        std::vector<Page> pages;
        uint activePage;

        sigc::connection keyboardConnection;

        Controller(std::string filename="");

        bool onKeyPress(GdkEventKey* event);
        bool onCtrlKeyPress(GdkEventKey* event);
        bool onAltKeyPress(GdkEventKey* event);
};

#endif

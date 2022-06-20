#include "global.h"
#include "page.h"

#include <iostream>

Page page;

bool onCtrlKeyPress(GdkEventKey* event) {
    // find keyval the list of command keys
    uint key_index = CC_COUNT;

    for(uint i = 0; i < CC_COUNT; i++) {
        if(commandKeys[i] == event->keyval & 0xFF) {
            key_index = i;
            break;
        }
    }

    // handle command events
    switch(key_index) {
        case CC_UNDO: page.undo(); break;
        case CC_REDO: page.redo(); break;
        case CC_SAVE: break;
        case CC_SAVE_AS: break;
        case CC_OPEN: break;
        case CC_CLOSE: break;
        case CC_FIND_REPLACE: break;
        case CC_AUTO_COMPLETE: break;
        case CC_AUTO_INDENT: break;
        case CC_WEB_ECHO: break;
        default:
            return false;
            break;
    }

    return true;
}

bool onAltKeyPress(GdkEventKey* event) {
    switch(event->keyval & 0xFF) {
        case UP: break;
        case DOWN: break;
        case LEFT: break;
        case RIGHT: break;
        default:
            return false;
            break;
    }

    return true;
}

bool onKeyPress(GdkEventKey* event) {
    if(event->state & Gdk::CONTROL_MASK) {
        return onCtrlKeyPress(event);
    } 

    if(event->state & Gdk::MOD1_MASK) {
        return onAltKeyPress(event);
    }

    page.record();

    switch(event->keyval & 0xFF) {
        case RETURN:
            page.preserveTabs();
            return true;
            break;
        default:
            return false;
            break;
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.yostlabs.shallot");

    Gtk::Window window;

    Gtk::ScrolledWindow body;

    body.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    body.set_size_request(256, 256);
    
    body.show();
    
    Gtk::TextView fileView;

    page.buffer_ptr = fileView.get_buffer();
    
    fileView.set_monospace();
    fileView.signal_key_press_event().connect(&onKeyPress, false);
    fileView.show();

    body.add(fileView);

    window.add(body);

    return app->run(window);
}


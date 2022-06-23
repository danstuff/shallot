#include "controller.h"

Controller::Controller(std::string filename) {
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    set_size_request(256, 256);

    // orient the line ruler to the left of the page view, which expands
    ruler.show();

    layout.pack_start(ruler, Gtk::PACK_SHRINK);
    
    activePage = 0;
    pages.push_back(Page(filename));

    pages[0].show();

    pages[0].signal_key_press_event().connect(
            sigc::mem_fun(*this, &Controller::onKeyPress), false);

    layout.pack_end(pages[0], Gtk::PACK_EXPAND_WIDGET);

    pages[0].grab_focus();

    layout.show();

    add(layout);
    show();
}

bool Controller::onKeyPress(GdkEventKey* event) {
    // TODO jump to cursor if off screen

    if(event->state & Gdk::CONTROL_MASK) {
        return onCtrlKeyPress(event);
    } 

    if(event->state & Gdk::MOD1_MASK) {
        return onAltKeyPress(event);
    }

    pages[activePage].record();

    switch(event->keyval & 0xFF) {
        case RETURN:
            pages[activePage].preserveTabs();
            //pages[activePage].preserveLineHeight();
            return true;
            break;
        case DELETE:
            //pages[activePage].preserveLineHeight();
            return false;
            break;
        case BACKSPACE:
            //pages[activePage].forceBackspace();
            //pages[activePage].preserveLineHeight();
            return false;
            break;
        default:
            return false;
            break;
    }
}

bool Controller::onCtrlKeyPress(GdkEventKey* event) {
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
        case CC_UNDO: pages[activePage].undo(); break;
        case CC_REDO: pages[activePage].redo(); break;
        case CC_SAVE_AS:
            pages[activePage].filename = "";
        case CC_SAVE:
            pages[activePage].save();
            break;
        case CC_OPEN: break;
        case CC_CLOSE: break;
        case CC_FIND_REPLACE: break;
        case CC_AUTO_COMPLETE: break;
        case CC_AUTO_INDENT: break;
        default:
            return false;
            break;
    }

    return true;
}

bool Controller::onAltKeyPress(GdkEventKey* event) {
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

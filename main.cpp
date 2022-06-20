#include "global.h"
#include "action.h"

#include <iostream>

ActionList actDone;
ActionList actUndone;

Gtk::TextView* fileViewPtr = nullptr;

uint countTabs() {
    TextBufferPtr tb_ptr = fileViewPtr->get_buffer();

    Gtk::TextIter line_indent = 
        tb_ptr->get_insert()->get_iter();
    
    line_indent.set_line_offset(0);

    uint tabs = 0;

    while(line_indent.get_char() == '\t') {
        tabs++;
        line_indent++;
    }

    return tabs;
}

bool onCtrlKeyPress(GdkEventKey* event) {
    // find keyval the list of command keys
    uint key_index = CC_COUNT;

    for(uint i = 0; i < CC_COUNT; i++) {
        if(commandKeys[i] == event->keyval) {
            key_index = i;
            break;
        }
    }

    // handle command events
    switch(key_index) {
        case CC_UNDO: 
            {
                Action a = actDone.pop();
                a.reverse(fileViewPtr->get_buffer());
                actUndone.push(a);
                break;
            }
        case CC_REDO: 
            {
                Action a = actUndone.pop();
                a.perform(fileViewPtr->get_buffer());
                actDone.push(a);
                break;
            }
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
    switch(event->keyval) {
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

    switch(event->keyval & 0xFF) {
        case RETURN:
            {
                uint tabCount = countTabs();
                std::string tabs = "\n";
                for(uint i = 0; i < tabCount; i++) {
                    tabs += '\t';
                }
                fileViewPtr->get_buffer()->insert_at_cursor(Glib::ustring(tabs));
                break;
            }
        default:
            return false;
            break;
    }

    return true;
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.yostlabs.shallot");

    Gtk::Window window;

    Gtk::ScrolledWindow body;

    body.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    body.set_size_request(256, 256);
    
    body.show();
    
    Gtk::TextView fileView;
    fileViewPtr = &fileView;
    
    fileView.set_monospace();
    fileView.signal_key_press_event().connect(&onKeyPress, false);
    fileView.show();

    body.add(fileView);

    window.add(body);

    return app->run(window);
}


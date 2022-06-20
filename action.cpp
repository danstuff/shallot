#include "action.h"

// ACTION

Action::Action() {
    nullify();
}

void Action::nullify() {
    remove = false;
    position = -1;
    content = "";
}

void Action::perform(TextBufferPtr buffer, bool reversed) {
    if(position == -1 || content.length() <= 0) return;
    Gtk::TextIter it;
    it.set_offset(position);

    if(remove != reversed) {
        Gtk::TextIter it_end;
        it_end.set_offset(position + content.length());

        buffer->erase(it, it_end);

    } else {
        buffer->insert(it, Glib::ustring(content));
    }
}

void Action::reverse(TextBufferPtr buffer) {
    perform(buffer, true);
}

// ACTION LIST

ActionList::ActionList() {
    start = 0;
    end = 0;
}

void ActionList::push(Action a) {
    if(a.position == -1) return;

    end++;

    if(end >= UNDO_LEVELS) end = 0;

    if(end == start) start++;

    if(start >= UNDO_LEVELS) start = 0;

    list[end] = a;
}

Action ActionList::pop() {
    Action a;

    if(end != start) {
        a = list[end];
        list[end].nullify();

        if(end > 0) {
            end--;
        } else {
            end = UNDO_LEVELS-1;
        }
    }

    return a;
}

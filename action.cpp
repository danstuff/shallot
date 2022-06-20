#include "action.h"

// ACTION

Action::Action() {
    nullify();
}

void Action::nullify() {
    position = -1;
    content = "";
}

void Action::perform(TextBufferPtr buffer) {
    if(position == -1 || content.length() <= 0) return;
    Gtk::TextIter it;
    it.set_offset(position);

    // TODO 
}

void Action::reverse(TextBufferPtr buffer) {
    // TODO how to reverse a backspaced character?
}

// ACTION LIST

ActionList::ActionList() {
    start = 0;
    end = 0;
}

void ActionList::push(Action a) {
    if(a.position == -1 || a.content.length() <= 0) return;

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

void ActionList::clear() {
    start = 0;
    end = 0;

    for(uint i = 0; i < UNDO_LEVELS; i++) {
        list[i].nullify();
    }
}

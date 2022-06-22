#include "page.h"

// PAGE STACK

PageStack::PageStack() {
    start = 0;
    end = 0;
}

void PageStack::push(Glib::ustring a) {
    if(a.length() <= 0) return;

    end++;

    if(end >= UNDO_LEVELS) end = 0;

    if(end == start) start++;

    if(start >= UNDO_LEVELS) start = 0;

    list[end] = a;
}

Glib::ustring PageStack::pop() {
    Glib::ustring a = "";

    if(end != start) {
        a = list[end];
        list[end] = "";

        if(end > 0) {
            end--;
        } else {
            end = UNDO_LEVELS-1;
        }
    }

    return a;
}

Glib::ustring PageStack::peek() {
    return list[end];
}

void PageStack::clear() {
    start = 0;
    end = 0;

    for(uint i = 0; i < UNDO_LEVELS; i++) {
        list[i] = "";
    }
}

// PAGE

Page::Page(std::string _filename) {
    actionCount = 0;
    filename = _filename;
    set_monospace();
    
    load();
}

void Page::undo() {
    if(doneStack.peek() != get_buffer()->get_text()) {
        record(true);
    }

    undoneStack.push(doneStack.pop());
    get_buffer()->set_text(doneStack.peek());
}

void Page::redo() {
    if(doneStack.peek() != get_buffer()->get_text()) {
        record(true);
    }

    doneStack.push(undoneStack.pop());
    get_buffer()->set_text(doneStack.peek());
}

void Page::record(bool force) {
    undoneStack.clear();

    actionCount++;

    if(force || actionCount >= ACTIONS_PER_RECORD) {
        doneStack.push(get_buffer()->get_text());
        actionCount = 0;
    }
}

void Page::save() {

}

void Page::load() {

}

void Page::preserveTabs() {
    Gtk::TextIter line_indent = 
        get_buffer()->get_insert()->get_iter();
    
    line_indent.set_line_offset(0);

    Glib::ustring tabs = "\n";

    while(line_indent.get_char() == '\t') {
        tabs += '\t';
        line_indent++;
    }

    get_buffer()->insert_at_cursor(tabs);
} 

void Page::preserveLineHeight() {
    int lines = get_buffer()->get_line_count();

    for(uint i = 0; i < lines; i++) {
        Gtk::TextIter line_start = 
            get_buffer()->get_iter_at_line(i);

        if(line_start.get_char() == '\n' ||
           line_start.get_char() == 0) {

            get_buffer()->insert(line_start, " ");
        }
    }
}

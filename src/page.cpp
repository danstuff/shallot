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
    set_pixels_above_lines(10);
    set_pixels_below_lines(10);
    set_pixels_inside_wrap(10);
    
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

std::string Page::chooseFile(Glib::ustring prompt, Gtk::FileChooserAction action) {
    Gtk::FileChooserDialog dialog("", action);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button(prompt, Gtk::RESPONSE_OK);

    if(dialog.run() == Gtk::RESPONSE_OK) 
        return std::string(dialog.get_filename());
    else
        return "";
}

void Page::load() {
    // choose a filename from a dialog
    if(filename == "") {
        filename = chooseFile("Open", Gtk::FILE_CHOOSER_ACTION_OPEN);
    }

    if(filename == "") return;

    // load the file into a string
    std::ifstream file_in(filename);

    std::string file_str((std::istreambuf_iterator<char>(file_in)),
                         (std::istreambuf_iterator<char>()));

    file_in.close();

    // set the text buffer
    get_buffer()->set_text(Glib::ustring(file_str));

    preserveLineHeight();
}

void Page::save() {
    // choose a filename from a dialog
    if(filename == "") {
        filename = chooseFile("Save", Gtk::FILE_CHOOSER_ACTION_SAVE);
    }

    if(filename == "") return;

    // write the buffer into a string, then the file
    std::string file_str(get_buffer()->get_text());

    std::ofstream file_out(filename);

    file_out << file_str;

    file_out.close();
}

void Page::preserveTabs() {
    // make sure the indentation remains the same after pressing enter
    Gtk::TextIter cursor = 
        get_buffer()->get_insert()->get_iter();

    Gtk::TextIter line_indent(cursor);
    
    line_indent.set_line_offset(0);

    Glib::ustring tabs = "\n";

    while(line_indent.get_char() == '\t' && line_indent != cursor) {
        tabs += '\t';
        line_indent++;
    }

    get_buffer()->insert_at_cursor(tabs);
} 

void Page::preserveLineHeight() {
    // make sure every line is the same height by inserting a
    // space character on the empty ones. yeah, it's pretty stupid. thanks GTK.
    int lines = get_buffer()->get_line_count();

    for(uint i = 0; i < lines-1; i++) {
        Gtk::TextIter line_start = 
            get_buffer()->get_iter_at_line(i);

        if(line_start.starts_line() && line_start.ends_line()) {

            get_buffer()->insert(line_start, " ");
        }
    }
}

void Page::forceBackspace() {
    //if a line is just a space, delete it
    Gtk::TextIter cursor = 
        get_buffer()->get_insert()->get_iter();

    Gtk::TextIter prev(cursor);
    prev--;

    if(prev.get_char() == ' ' && prev.starts_line() && cursor.ends_line()) {
        get_buffer()->backspace(cursor);

    }    
}

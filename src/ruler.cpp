#include "ruler.h"
    
Ruler::Ruler() {
    set_monospace();

    Glib::ustring numbers = "";
    for(uint i = 1; i <= 999; i++) {
        Glib::ustring spaces = "";

        if(i <= 9) spaces = "  ";
        else if(i <= 99) spaces = " ";

        numbers += spaces + std::to_string(i) + " \n";
    }

    Glib::RefPtr<Gtk::TextTag> grey_tag = Gtk::TextTag::create();
    grey_tag->property_foreground() = "grey";

    TextBufferPtr lineBuf = get_buffer();

    lineBuf->get_tag_table()->add(grey_tag);

    Gtk::TextIter it = lineBuf->get_insert()->get_iter();

    lineBuf->insert_with_tag(it, numbers, grey_tag);

    set_editable(false);
    set_cursor_visible(false);
}


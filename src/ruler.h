#ifndef RULER_H
#define RULER_H

#include "global.h"

const Glib::ustring RULER_TEXT_COLOR = "grey";

class Ruler : public Gtk::TextView {
    public:

        Ruler();

        // TODO make ruler scale to file length
};

#endif

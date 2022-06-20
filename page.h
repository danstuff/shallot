#ifndef PAGE_H
#define PAGE_H

#include "global.h"

const uint UNDO_LEVELS = 512;
const uint ACTIONS_PER_RECORD = 4;

class PageStack {
    private:
        Glib::ustring list[UNDO_LEVELS];
        uint start, end;

    public:
        PageStack();

        void push(Glib::ustring a);
        Glib::ustring pop();
        Glib::ustring peek();

        void clear();
};

class Page {
    private:
        PageStack doneStack, undoneStack;
        uint actionCount;

    public:
        std::string filename;
        TextBufferPtr buffer_ptr;

        Page(std::string _filename="");

        void undo();
        void redo();

        void record(bool force=false);

        void save();
        void load();

        void preserveTabs();

};

#endif

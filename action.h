#ifndef ACTION_H
#define ACTION_H

#include "global.h"

const uint UNDO_LEVELS = 512;

class Action {
    public:
        bool remove;
        int position;
        std::string content;

        Action();

        void nullify();

        void perform(TextBufferPtr buffer, bool reversed = false);
        void reverse(TextBufferPtr buffer);
};

class ActionList {
    private:
        Action list[UNDO_LEVELS];
        uint start, end;

    public:
        ActionList();

        void push(Action a);
        Action pop();
};

#endif

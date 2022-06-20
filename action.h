#ifndef ACTION_H
#define ACTION_H

#include "global.h"

const uint UNDO_LEVELS = 1024;

class Action {
    public:
        int position;
        std::string content;

        Action();

        void nullify();

        void perform(TextBufferPtr buffer);
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

        void clear();
};

#endif

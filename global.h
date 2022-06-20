#ifndef GLOBAL_H
#define GLOBAL_H

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/textview.h>

typedef unsigned int uint;
typedef Glib::RefPtr<Gtk::TextBuffer> TextBufferPtr;

enum CtrlCommands {
    CC_UNDO,
    CC_REDO,
    CC_SAVE,
    CC_SAVE_AS,
    CC_OPEN,
    CC_CLOSE,
    CC_FIND_REPLACE,
    CC_AUTO_COMPLETE,
    CC_AUTO_INDENT,
    CC_WEB_ECHO,
    CC_COUNT
};

const char ESCAPE = 0x1B;
const char RETURN = 0x0D;   
const char TAB = 0x09;
const char BACKSPACE = 0x08;
const char DELETE = 0xFF;

const char LEFT = 0x51;
const char UP = 0x52;
const char RIGHT = 0x53;
const char DOWN = 0x54;

const char breakChars[] = {
    '\n',
    ' ',
    '%',
    '&',
    '*',
    '+',
    '-',
    '.',
    '/',
    '=',
    '^',
    '_',
    '|'
};

const char encloseCharsL[] = {
    '{',
    '[',
    '('
};

const char encloseCharsR[] = {
    '}',
    ']',
    ')'
};

const char commandKeys[] = {
    'z',
    'y',
    's',
    'S',
    'a',
    'q',
    'f',
    ' ',
    TAB,
    'e',
};
        
#endif

#include "input_decoder.h"
#include <stdbool.h>
#include <ncurses.h>

static inline bool is_typing_char(int ch)
{
    return ch >= 32 && ch <= 126;  // printable ascii
}

static inline bool is_backspace(int ch)
{
    return ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127 || ch == '\b';
}

InputEvent decode_input(int ch)
{
    InputEvent ev;
    bool bksp = is_backspace(ch);
    if (is_typing_char(ch) || bksp) {
        ev.type = INPUT_TYPING;
        ev.typing.inputted = ch;
        ev.typing.is_backspace = bksp;
        // more handling required in typing test
        return ev;
    }
    switch (ch)
    {
    case KEY_UP:
        ev.type = INPUT_MENU;
        ev.menu.type = M_ARROW_UP;
        return ev;
    case KEY_DOWN:
        ev.type = INPUT_MENU;
        ev.menu.type = M_ARROW_DOWN;
        return ev;
    case KEY_LEFT:
        ev.type = INPUT_MENU;
        ev.menu.type = M_ARROW_LEFT;
        return ev;
    case KEY_RIGHT:
        ev.type = INPUT_MENU;
        ev.menu.type = M_ARROW_RIGHT;
        return ev;
    case '\n':
    case KEY_ENTER:
        ev.type = INPUT_MENU;
        ev.menu.type = M_ENTER;
        return ev;
    case '\t':
        ev.type = INPUT_MENU;
        ev.menu.type = M_TAB;
        return ev;
    case ERR:
        ev.type = INPUT_NONE;
        ev.illegal.error_code = ch;
        return ev;
    default:
        ev.type = INPUT_ILLEGAL;
        ev.illegal.error_code = ch;
        return ev;
    }
}

/* This function will await until a char is inputted. unless timeout is set!*/
InputEvent get_input()
{
    int ch = getch();
    return decode_input(ch);
}
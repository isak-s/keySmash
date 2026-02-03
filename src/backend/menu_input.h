#ifndef INPUT_H
#define INPUT_H

#include "ui/ui_panel_curses.h"

#include "app/app_context.h"

/* handle special characters like tab and arrow keys.
If alphanumerical, return a TypingTestInput */
typedef enum {
    M_ARROW_UP,
    M_ARROW_DOWN,
    M_ARROW_LEFT,
    M_ARROW_RIGHT,
    M_TAB,
    M_SHIFT_TAB,
    M_ENTER
} MenuInputType;

typedef struct {
    MenuInputType type;
} MenuInput;

void handle_menu_input(UIPanelCurses* menu, MenuInput* inp, AppContext* app);

#endif

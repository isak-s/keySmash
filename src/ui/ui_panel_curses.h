#ifndef UI_PANEL_CURSES_H
#define UI_PANEL_CURSES_H

#include "backend/ui_panel.h"
#include <ncurses.h>

typedef struct {
    UIPanel* panel;        // pointer to logical panel
    WINDOW* cont_win;     // inner content curses window
    WINDOW* border_win;  // outer window
    int currRow;  // which row of menu item to draw
} UIPanelCurses;

// Create curses wrapper for a panel
UIPanelCurses ui_panel_curses_create(UIPanel* panel);

// Draw panel + all elements
void ui_panel_curses_draw(const UIPanelCurses* panel_curses);

// Destroy curses resources
void ui_panel_curses_destroy(UIPanelCurses* panel_curses);

#endif

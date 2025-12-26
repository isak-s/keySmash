#include "ui_panel_curses.h"
#include <ncurses.h>

UIPanelCurses ui_panel_curses_create(const UIPanel* panel) {
    WINDOW* win = newwin(panel->height, panel->width, panel->y, panel->x);
    box(win, 0, 0);

    UIPanelCurses pc = {
        .panel = panel,
        .win = win
    };
    return pc;
}

void ui_panel_curses_draw(const UIPanelCurses* panel_curses) {
    werase(panel_curses->win);
    box(panel_curses->win, 0, 0);

    wmove(panel_curses->win, 1, 1);

    for (size_t i = 0; i < panel_curses->panel->element_count; ++i) {
        UIElement* el = &panel_curses->panel->elements[i];
        el->draw(el, (void*)panel_curses);
    }
    wrefresh(panel_curses->win);
}

void ui_panel_curses_destroy(UIPanelCurses* panel_curses) {
    delwin(panel_curses->win);
}

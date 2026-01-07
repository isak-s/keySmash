#include "ui_panel_curses.h"
#include <ncurses.h>
#include <stdlib.h>
#include "ui_constants.h"

UIPanelCurses ui_panel_curses_create(UIPanel* panel) {

    WINDOW* border_win = newwin(
        panel->height,
        panel->width,
        panel->y,
        panel->x
    );
    box(border_win, 0, 0);

    WINDOW* win = newwin(
        panel->height - UI_BORDER_PADDING,
        panel->width - UI_BORDER_PADDING,
        panel->y + 1,
        panel->x + 1
    );
    scrollok(win, TRUE); // allow scrolling

    return (UIPanelCurses) {
        .panel = panel,
        .border_win = border_win,
        .cont_win = win
    };
}

void ui_panel_curses_draw(const UIPanelCurses* panel_curses) {
    werase(panel_curses->cont_win);

    box(panel_curses->border_win, 0, 0);

    wmove(panel_curses->cont_win, 0, 0);

    for (size_t i = 0; i < panel_curses->panel->element_count; ++i) {
        UIElement* el = &panel_curses->panel->elements[i];
        el->draw(el, (void*)panel_curses);
    }

    wrefresh(panel_curses->border_win); // must redraw border before inner win!!
    wrefresh(panel_curses->cont_win);
}

void ui_panel_curses_destroy(UIPanelCurses* panel_curses) {
    delwin(panel_curses->cont_win);
    delwin(panel_curses->border_win);
    // this could be moved to a function in ui_panel.c
    for (size_t i = 0; i < panel_curses->panel->element_count; i++) {
        free(panel_curses->panel->elements[i].impl);
    }
    free(panel_curses->panel->elements);
    free(panel_curses->panel);
}

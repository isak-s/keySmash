#include <ncurses.h>
#include "ui_panel_curses.h"
#include "menu_adapter.h"

int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    // logical panel
    UIPanel panel = {
        .width = 30,
        .height = 10,
        .x = 5,
        .y = 5,
        .element_count = 2
    };

    MenuItem item1 = { .text = "Start", .enabled = true };
    MenuItem item2 = { .text = "Quit", .enabled = true };

    UIElement elements[2];
    elements[0] = ui_menu_item_create(&item1);
    elements[1] = ui_menu_item_create(&item2);

    panel.elements = elements;

    // curses wrapper
    UIPanelCurses pc = ui_panel_curses_create(&panel);

    ui_panel_curses_draw(&pc);

    wrefresh(pc.win);

    int cx = 20;
    int cy = 20;
    getch();
    char c = ' ';
    while(c != 'q') {
        wmove(stdscr, cx++, cy++);
        char c = getch();
    }

    ui_panel_curses_destroy(&pc);
    endwin();
    return 0;
}

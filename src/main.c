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
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    int element_count = 4;
    UIPanel panel = {
        .width = max_x-10,  // 5 char padding on each side
        .height = element_count + 2, // for border
        .x = 5,
        .y = 2,
        .element_count = element_count
    };

    MenuItem item1 = { .text = "Start typing", .enabled = true };
    MenuItem item2 = { .text = "Statistics", .enabled = true };
    MenuItem item4 = { .text = "Mode", .enabled = true };
    MenuItem item3 = { .text = "QUIT", .enabled = true };

    UIElement elements[element_count];
    elements[0] = ui_menu_item_create(&item1);
    elements[1] = ui_menu_item_create(&item2);
    elements[2] = ui_menu_item_create(&item4);
    elements[3] = ui_menu_item_create(&item3);

    panel.elements = elements;

    // curses wrapper
    UIPanelCurses pc = ui_panel_curses_create(&panel);

    ui_panel_curses_draw(&pc);

    wrefresh(pc.win);

    UIPanel test_area = {
        .width = max_x - 10,
        .height = max_y / 3,
        .x = 5,
        .y = 9,
        .element_count = 0
    };

    UIPanelCurses ta = ui_panel_curses_create(&test_area);

    ui_panel_curses_draw(&ta);
    wrefresh(ta.win);

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

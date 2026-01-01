#include <ncurses.h>
#include "ui_panel_curses.h"
#include "menu_adapter.h"
#include <stdlib.h>
#include "ui_commands.h"
#include "typing_test_input.h"
#include "typing_test.h"
#include "menu.h"


int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    // logical panel

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    UIPanelCurses main_menu = menu_main_create(max_x);

    ui_panel_curses_draw(&main_menu);
    wrefresh(main_menu.win);

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

    wmove(ta.win, 1, 1);
    DrawCommand dc = new_draw_char_command('A');
    dc.execute(&dc, ta.win);
    wmove(ta.win, 1, 4);
    dc = new_draw_char_command('B');

    dc.execute(&dc, ta.win);
    wrefresh(ta.win);

    // iterates over all chars in the text, and creates draw commands for all of them.
    TypingTest tt = typing_test_new_english("this is an example typing test");
    // draw all chars

    // user types over the already written text, but in a different color.

    int cx = 1;
    int cy = 2;
    char c = ' ';
    while(c != 'q') {
        wmove(ta.win, cy, cx++);
        TypingTestInput inp = get_input(&tt);
        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, ta.win);

        wrefresh(ta.win);

        if (cx >= ta.panel->width-1) { // - 1 for border
            cy++;
            cx = 1;
        }
    }
    free(main_menu.panel->elements);
    // free(main_menu.panel);
    ui_panel_curses_destroy(&main_menu);
    ui_panel_curses_destroy(&ta);
    endwin();
    return 0;
}

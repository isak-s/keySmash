#include <ncurses.h>
#include "ui_panel_curses.h"
#include "menu_adapter.h"
#include <stdlib.h>
#include "ui_commands.h"
#include "typing_test_input.h"
#include "typing_test.h"
#include "menu.h"
#include "render_context.h"


int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    // logical panel

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    static int border_padding = 2;

    UIPanelCurses main_menu = menu_main_create(max_x);

    ui_panel_curses_draw(&main_menu);
    wrefresh(main_menu.win);


    UIPanel test_area = {
        .width = max_x - 10,
        .height = max_y / 3,
        .x = 5,
        .y = main_menu.panel->element_count + border_padding * 2,
        .element_count = 0
    };

    UIPanelCurses ta = ui_panel_curses_create(&test_area);
    RenderContext ta_ctx = render_context_new(ta.win);

    ui_panel_curses_draw(&ta);
    wrefresh(ta.win);

    // iterates over all chars in the text, and creates draw commands for all of them.
    TypingTest tt = typing_test_new_english("this is an example typing test");
    // draw all chars
    typing_test_execute_draw_queue(&tt, &ta_ctx);
    // user types over the already written text, but in a different color.

    while(true) {
        TypingTestInput inp = get_input(&tt);
        // UICommand from input. can be tab, shift tab or enter to navigate menu.
        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, &ta_ctx);
        render_context_handle_screen_wrapping(&ta_ctx);
        wrefresh(ta.win);
    }
    free(main_menu.panel->elements);
    // free(main_menu.panel);
    ui_panel_curses_destroy(&main_menu);
    ui_panel_curses_destroy(&ta);
    endwin();
    return 0;
}

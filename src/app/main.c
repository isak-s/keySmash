#include <ncurses.h>
#include "ui/ui_panel_curses.h"
#include <stdlib.h>
#include "ui/ui_commands.h"
#include "domain/typing_test_input.h"
#include "domain/typing_test.h"
#include "menu.h"
#include "ui/render_context.h"
#include "ui/ui_constants.h"

int main(void) {
    initscr();

    if (!has_colors()) {
        endwin();
        fprintf(stderr, "Unsupported terminal! Terminal must support colors.");
        exit(1);
    }
    start_color();
    use_default_colors();

    init_pair(1, COLOR_GREEN, -1); // 1 = pair number, -1 = default background
    init_pair(2, COLOR_RED, -1); // 1 = pair number, -1 = default background

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    UIPanelCurses main_menu = menu_main_create(max_x);

    ui_panel_curses_draw(&main_menu);
    wrefresh(main_menu.win);


    UIPanel test_area = {
        .width = max_x - 10,
        .height = max_y / 3,
        .x = 5,
        .y = main_menu.panel->element_count + UI_BORDER_PADDING * 2,
        .element_count = 0
    };

    UIPanelCurses ta = ui_panel_curses_create(&test_area);
    RenderContext ta_ctx = render_context_new(ta.win);

    ui_panel_curses_draw(&ta);
    wrefresh(ta.win);

    // iterates over all chars in the text, and creates draw commands for all of them.
    TypingTest tt = typing_test_new_english("this is an example typing test lorem ipsum dolor sit amet tntntntntntntntntntntntntntntntntntntntntntntntntntntntntntnt");
    // draw all chars
    typing_test_execute_draw_queue(&tt, &ta_ctx);
    // user types over the already written text, but in a different color.

    while(true) {
        TypingTestInput inp = get_input(&tt, &ta_ctx);
        // UICommand from input. can be tab, shift tab or enter to navigate menu.
        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, &ta_ctx);
        increment_cursor(&ta_ctx);
        wmove(ta.win, ta_ctx.cy, ta_ctx.cx);
        wrefresh(ta.win);
    }
    free(main_menu.panel->elements);
    // free(main_menu.panel);
    ui_panel_curses_destroy(&main_menu);
    ui_panel_curses_destroy(&ta);
    endwin();
    return 0;
}

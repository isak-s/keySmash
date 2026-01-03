#include <ncurses.h>
#include "ui/ui_panel_curses.h"
#include <stdlib.h>
#include "ui/ui_commands.h"
#include "domain/typing_test_input.h"
#include "domain/typing_test.h"
#include "menu.h"
#include "ui/render_context.h"
#include "ui/ui_constants.h"
#include "ui/colors.h"

#include "test_area.h"

int main(void) {
    initscr();
    init_color_scheme(CYBERPUNK_FEVER_DREAM);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    UIPanelCurses main_menu = menu_main_create(max_x);

    ui_panel_curses_draw(&main_menu);

    int ta_y = main_menu.panel->element_count + UI_BORDER_PADDING * 2;
    UIPanelCurses ta = test_area_create(max_x, ta_y, max_y);

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

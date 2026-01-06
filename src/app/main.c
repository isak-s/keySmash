#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "domain/typing_test_input.h"
#include "domain/typing_test.h"
#include "ui/render_context.h"
#include "ui/ui_constants.h"
#include "ui/colors.h"
#include "ui/ui_commands.h"
#include "ui/ui_panel_curses.h"

#include "test_area.h"
#include "menu.h"

int main(void) {
    initscr();
    init_color_scheme(stdscr, TRON_ORANGE);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    UIPanelCurses main_menu = menu_main_create(max_x);
    init_color_scheme(main_menu.win, TRON_ORANGE);

    int ta_y = main_menu.panel->element_count + UI_BORDER_PADDING * 2;
    UIPanelCurses ta = test_area_create(max_x, ta_y, max_y);
    init_color_scheme(ta.win, TRON_ORANGE);

    RenderContext ta_ctx = render_context_new(ta.win);

    ui_panel_curses_draw(&main_menu);
    ui_panel_curses_draw(&ta);

    // iterates over all chars in the text, and creates draw commands for all of them.
    TypingTest tt = typing_test_new_english("this is an example typing test lorem ipsum dolor sit amet");
    typing_test_execute_draw_queue(&tt, &ta_ctx);
    // user types over the already written text, but in a different color.

    while(tt.idx < strlen(tt.text) - 1) {
        TypingTestInput inp = get_input(&tt, &ta_ctx);
        // UICommand from input. can be tab, shift tab or enter to navigate menu.
        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, &ta_ctx);
        wrefresh(ta.win);
    }

    // show statistics:

    ui_panel_curses_destroy(&main_menu);
    ui_panel_curses_destroy(&ta);
    endwin();
    return 0;
}

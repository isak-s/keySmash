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
#include "domain/statistics.h"

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
    Statistics stat = statistics_create();

    int ta_y = main_menu.panel->element_count + UI_BORDER_PADDING * 2;
    int stat_y = max_y / 3 + ta_y;

    UIPanelCurses ta = test_area_create(max_x, ta_y, max_y);
    UIPanelCurses statistics_panel = statistics_panel_create(max_x, stat_y, &stat);


    init_color_scheme(ta.border_win, TRON_ORANGE);
    init_color_scheme(ta.cont_win, TRON_ORANGE);

    init_color_scheme(main_menu.border_win, TRON_ORANGE);
    init_color_scheme(main_menu.cont_win, TRON_ORANGE);

    init_color_scheme(statistics_panel.border_win, TRON_ORANGE);
    init_color_scheme(statistics_panel.cont_win, TRON_ORANGE);

    RenderContext ta_ctx = render_context_new(ta.cont_win);

    ui_panel_curses_draw(&statistics_panel);
    ui_panel_curses_draw(&main_menu);
    ui_panel_curses_draw(&ta);

    // iterates over all chars in the text, and creates draw commands for all of them.
    TypingTest tt = typing_test_new_english();
    typing_test_execute_draw_queue(&tt, &ta_ctx);
    // user types over the already written text, but in a different color.

    while(true) {
        TypingTestInput inp = get_input(&tt);

        int i = 0;
        char c;
        while ((c = typing_test_get_char(&tt, tt.cursor + i)) != ' ' &&
               c != '\0' &&
               i < 32 - 1)
        {
            stat.currword[i++] = c;
        }

        stat.currword[i] = '\0';

        statistics_update(&stat, &inp);
        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, &ta_ctx);

        if (ta_ctx.cx == 1 && ta_ctx.cy == 2) {
            bool scrolled = scroll_window_upwards(&ta_ctx);
            int x = ta_ctx.cx;
            int y = ta_ctx.cy;
            ta_ctx.cx = 1;
            ta_ctx.cy = ta_ctx.max_y;
            if (scrolled) typing_test_execute_draw_queue(&tt, &ta_ctx);
            ta_ctx.cx = x;
            ta_ctx.cy = y;
            redraw_cursor(&ta_ctx);
        }
        // UICommand from input. can be tab, shift tab or enter to navigate menu.
        ui_panel_curses_draw(&statistics_panel);
        wrefresh(statistics_panel.cont_win);
        wrefresh(ta.cont_win);
    }
    // show statistics:

    ui_panel_curses_destroy(&main_menu);
    ui_panel_curses_destroy(&ta);
    ui_panel_curses_destroy(&statistics_panel);
    typing_test_destroy(&tt);
    endwin();
    return 0;
}

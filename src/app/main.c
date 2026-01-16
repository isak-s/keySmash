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
#include "backend/input_decoder.h"
#include "app_context.h"

void statistics_set_curr_word(TypingTest* tt, Statistics* stat)
{
    int i = 0;
    char c;
    while ((c = typing_test_get_char(tt, tt->cursor + i)) != ' ' &&
           c != '\0' &&
           i < 32 - 1)
    {
        stat->currword[i++] = c;
    }
    stat->currword[i] = '\0';
}

int main(void) {
    AppContext app = { .state = APP_STARTUP };

    while(app.state != APP_QUIT) {
        switch (app.state)
        {
        case APP_STARTUP:
            init_app(&app);
            break;
        case APP_NEW_TEST:
            // statistics_reset(&stat);
            app.typing_test = typing_test_new_english();
            app.ta_ctx = render_context_new(app.testarea.cont_win);
            wclear(app.ta_ctx.win);
            typing_test_execute_draw_queue(&app.typing_test, &app.ta_ctx);
            statistics_set_curr_word(&app.typing_test, &app.statistics);
            ui_panel_curses_draw(&app.statistics_panel);
            wrefresh(app.statistics_panel.cont_win);
            redraw_cursor(&app.ta_ctx);
            wrefresh(app.testarea.cont_win);
            app.next_state = APP_IN_TEST;
            break;
        case APP_IN_TEST:
            InputEvent ev = get_input();
            switch (ev.type)
            {
            case INPUT_MENU:
                handle_menu_input(&app.main_menu, &ev.menu, &app);
                ui_panel_curses_draw(&app.main_menu);
                redraw_cursor(&app.ta_ctx);
                wrefresh(app.testarea.cont_win);
                break;
            case INPUT_TYPING:
                TypingTestInput inp = ev.typing;

                if (inp.is_backspace && !backspace_allowed(&app.ta_ctx))
                {
                    ev.type = INPUT_ILLEGAL;
                    break;
                }
                typing_test_handle_input(&app.typing_test, &inp);

                statistics_set_curr_word(&app.typing_test, &app.statistics);
                statistics_update(&app.statistics, &inp);

                DrawCommand dc = draw_command_from_input(&inp);
                dc.execute(&dc, &app.ta_ctx);

                if (app.ta_ctx.cx == 1 && app.ta_ctx.cy == 2)
                {
                    bool scrolled = scroll_window_upwards(&app.ta_ctx);
                    if (scrolled)
                        typing_test_execute_draw_queue(&app.typing_test, &app.ta_ctx);
                }
                ui_panel_curses_draw(&app.statistics_panel);
                wrefresh(app.statistics_panel.cont_win);
                wrefresh(app.testarea.cont_win);
                break;
            case INPUT_ILLEGAL:
                break;
            }
        default:
            break;
        }
        app.state = app.next_state;
    }

    destroy_app(&app);
    return 0;
}

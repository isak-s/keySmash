#include "app_state_handler.h"

#include "backend/input_decoder.h"
#include "menu.h"
#include "domain/typing_test.h"
#include "ui/ui_commands.h"


void app_handle_startup(AppContext* app)
{
    init_app(app);
    app->next_state = APP_NEW_TEST;
}

void app_handle_new_test(AppContext* app)
{
    // if (old test) cleanup old test
    statistics_reset(&app->statistics);
    app->typing_test = typing_test_new_english();
    app->ta_ctx = render_context_new(app->testarea.cont_win);
    wclear(app->ta_ctx.win);
    typing_test_execute_draw_queue(&app->typing_test, &app->ta_ctx);
    typing_test_get_curr_word(&app->typing_test, app->statistics.currword);
    ui_panel_curses_draw(&app->statistics_panel);
    wrefresh(app->statistics_panel.cont_win);
    redraw_cursor(&app->ta_ctx);
    wrefresh(app->testarea.cont_win);

    app->next_state = APP_IN_TEST;
}

void app_handle_in_test(AppContext* app)
{
    InputEvent ev = get_input();
    switch (ev.type)
    {
    case INPUT_MENU:
        handle_menu_input(&app->main_menu, &ev.menu, app);
        ui_panel_curses_draw(&app->main_menu);
        redraw_cursor(&app->ta_ctx);
        wrefresh(app->testarea.cont_win);
        break;
    case INPUT_TYPING:
        TypingTestInput inp = ev.typing;

        if (inp.is_backspace && !backspace_allowed(&app->ta_ctx)) {
            ev.type = INPUT_ILLEGAL;
            break;
        }
        typing_test_handle_input(&app->typing_test, &inp);

        typing_test_get_curr_word(&app->typing_test, app->statistics.currword);
        statistics_update(&app->statistics, &inp);

        DrawCommand dc = draw_command_from_input(&inp);
        dc.execute(&dc, &app->ta_ctx);

        if (app->ta_ctx.cx == 1 && app->ta_ctx.cy == 2)
        {
            bool scrolled = scroll_window_upwards(&app->ta_ctx);
            if (scrolled)
                typing_test_execute_draw_queue(&app->typing_test, &app->ta_ctx);
        }
        ui_panel_curses_draw(&app->statistics_panel);
        wrefresh(app->statistics_panel.cont_win);
        wrefresh(app->testarea.cont_win);
        break;
    case INPUT_ILLEGAL:
        break;
    }
}

void app_handle_quit(AppContext* app)
{
    destroy_app(app);
    app->next_state = APP_TERMINATED;
    app = NULL;
}
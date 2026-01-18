#include "app_state_handler.h"

#include "backend/input_decoder.h"
#include "menu.h"
#include "domain/typing_test.h"
#include "ui/ui_commands.h"
#include "domain/clock_helper.h"
#include "ui/ui_misc.h"


void app_handle_startup(AppContext* app)
{
    init_app(app);
    app->next_state = APP_NEW_TEST;
}

void app_handle_new_test(AppContext* app)
{
    // if (old test) cleanup old test
    statistics_reset(&app->statistics);
    app->typing_test = typing_test_new_english_200();
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
    // how can i do this without waiting for the input?
    InputEvent ev = get_input();

    if (app->typing_test.is_finished(&app->typing_test)) {
        app->next_state = APP_TEST_FINISHED;
        return;
    }

    ui_draw_typing_test_time_left(
        &app->typing_test,
        app->testarea.border_win,
        app->ta_ctx.max_x);

    switch (ev.type)
    {
    case INPUT_MENU:
        handle_menu_input(&app->main_menu, &ev.menu, app);
        ui_panel_curses_draw(&app->main_menu);
        redraw_cursor(&app->ta_ctx);
        wrefresh(app->testarea.cont_win);
        break;
    case INPUT_TYPING:
        if (!app->typing_test.start_timestamp) {
            app->typing_test.start_timestamp = now_ms();
        }
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

        if (scroll_window_upwards(&app->ta_ctx))
            typing_test_execute_draw_queue(&app->typing_test, &app->ta_ctx);

        ui_panel_curses_draw(&app->statistics_panel);
        wrefresh(app->statistics_panel.cont_win);
        wrefresh(app->testarea.cont_win);
        break;
    case INPUT_ILLEGAL:
        break;
    }
}

#include <stdlib.h>

void app_play_replay(AppContext* app)
{
    // iterate over input_history
    // create drawcommand from it
    // if (sleep_time) sleep(sleep_time)
    // dc.execute(&dc, &app->ta_ctx);
    app->ta_ctx.cy = 1;
    app->ta_ctx.cx = 1;

    TypingTestInput *prev = NULL;
    TypingTestInput *inp;

    while ((inp = fifo_q_pop(&app->typing_test.input_history)))
    {
        int64_t sleep_time = 0;

        if (prev)
        {
            sleep_time = inp->time_since_test_start - prev->time_since_test_start;
            if (sleep_time > 0)
                sleep_ms(sleep_time);
        }

        DrawCommand dc = draw_command_from_input(inp);
        
        dc.execute(&dc, &app->ta_ctx);
        wrefresh(app->ta_ctx.win);

        free(prev); // free only AFTER last use
        prev = inp;
    }

free(prev);

}


void app_handle_test_finished(AppContext* app)
{
    snprintf(app->statistics.currword,
             sizeof(app->statistics.currword),
             "%s",
             "test finished");
    ui_panel_curses_draw(&app->statistics_panel);
    wrefresh(app->statistics_panel.cont_win);

    wclear(app->ta_ctx.win);
    wrefresh(app->ta_ctx.win);


    app_play_replay(app);
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
        break;
    case INPUT_ILLEGAL:
        break;
    }
}

void app_handle_quit(AppContext* app)
{
    destroy_app(app);
    app->next_state = APP_TERMINATED;
}
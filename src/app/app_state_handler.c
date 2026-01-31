#include "app_state_handler.h"

#include "backend/input_decoder.h"
#include "menu.h"
#include "domain/typing_test.h"
#include "ui/ui_commands.h"
#include "domain/clock_helper.h"
#include "ui/ui_misc.h"

// initial state
void app_handle_startup(AppContext* app)
{
    init_app(app);
    app->next_state = APP_NEW_TEST;
}

void cleanup_old_typing_test(AppContext* app)
{
    if (app->typing_test.initialized)
        typing_test_destroy(&app->typing_test);
}

// transition state
void app_handle_new_test(AppContext* app)
{
    cleanup_old_typing_test(app);
    app->typing_test = typing_test_new_english_200();
    statistics_reset(&app->statistics);
    render_context_reset(&app->ta_ctx);

    wclear(app->ta_ctx.win);
    typing_test_execute_draw_queue(&app->typing_test, &app->ta_ctx);
    typing_test_get_curr_word(&app->typing_test, app->statistics.currword);
    ui_panel_curses_draw(&app->statistics_panel);
    wrefresh(app->statistics_panel.cont_win);
    redraw_cursor(&app->ta_ctx);
    wrefresh(app->testarea.cont_win);

    app->next_state = APP_IN_TEST;
}

// main game loop state
void app_handle_in_test(AppContext* app)
{
    if (app->typing_test.is_finished(&app->typing_test)) {
        app->next_state = APP_TEST_FINISHED;
        return;
    }

    ui_draw_typing_test_time_left(
        &app->typing_test,
        app->testarea.border_win,
        app->ta_ctx.max_x);
    redraw_cursor(&app->ta_ctx);
    wrefresh(app->testarea.cont_win); // have to do this so that if we redraw time left we move the cursor away from it

    InputEvent ev = get_input();

    switch (ev.type)
    {
    case INPUT_MENU:
        handle_menu_input(&app->main_menu, &ev.menu, app);
        ui_panel_curses_draw(&app->main_menu);
        redraw_cursor(&app->ta_ctx);
        wrefresh(app->testarea.cont_win);
        return;
    case INPUT_TYPING:
        if (!app->typing_test.start_timestamp) {
            app->typing_test.start_timestamp = now_ms();
        }
        TypingTestInput inp = ev.typing;

        if (inp.is_backspace && !backspace_allowed(&app->ta_ctx)) {
            ev.type = INPUT_ILLEGAL;
            return;
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
        return;
    case INPUT_NONE:    return;
    case INPUT_ILLEGAL: return;
    }
}

#include <stdlib.h>

// transition state
void app_handle_test_finished(AppContext* app)
{
     snprintf(app->statistics.currword,
             sizeof(app->statistics.currword),
             "%s",
             "test finished");
    ui_panel_curses_draw(&app->statistics_panel);
    wrefresh(app->statistics_panel.cont_win);
    wclear(app->ta_ctx.win);
    app->ta_ctx.cx = 1;
    app->ta_ctx.cy = 1;
    wrefresh(app->ta_ctx.win);
    app->next_state = APP_IN_REPLAY;
}

void replay_single_input(AppContext* app)
{
    if (!app->replay_state.start_timestamp) {
        app->replay_state.start_timestamp = now_ms();
        return;
    }
    if (app->typing_test.input_history.first == NULL) {
        app->next_state = APP_NEW_TEST;
        return;
    }
    // peek
    TypingTestInput* inp = app->typing_test.input_history.first->cmd;

    int64_t time_since_replay_start = app->replay_state.start_timestamp + inp->time_since_test_start;
    if (now_ms() < time_since_replay_start) {
        return;
    }
    // pop
    inp = fifo_q_pop(&app->typing_test.input_history);
    DrawCommand dc = draw_command_from_input(inp);

    dc.execute(&dc, &app->ta_ctx);
    scroll_window_upwards(&app->ta_ctx);
    wrefresh(app->ta_ctx.win);

    free(inp);
}

// play replay until user input
void app_handle_replay(AppContext* app)
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
    default: break;
    }
    replay_single_input(app);
    if (app->next_state != APP_IN_REPLAY) {
        app->replay_state.start_timestamp = 0;
        return;
    }
}

// transition to shutdown
void app_handle_quit(AppContext* app)
{
    destroy_app(app);
    app->next_state = APP_TERMINATED;
}
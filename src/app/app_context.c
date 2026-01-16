#include "app_context.h"
#include "ncurses.h"

#include "menu.h"
#include "ui/ui_constants.h"
#include "test_area.h"

void init_curses()
{
    initscr();
    init_color_scheme(stdscr, TRON_ORANGE);

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
}

void init_app_color_sceme(AppContext* app)
{
    init_color_scheme(app->testarea.border_win, app->color_scheme);
    init_color_scheme(app->testarea.cont_win, app->color_scheme);

    init_color_scheme(app->main_menu.border_win, app->color_scheme);
    init_color_scheme(app->main_menu.cont_win, app->color_scheme);

    init_color_scheme(app->statistics_panel.border_win, app->color_scheme);
    init_color_scheme(app->statistics_panel.cont_win, app->color_scheme);
}

void init_app_defaults(AppContext* app)
{
    app->color_scheme = TRON_ORANGE;
    app->typing_test_mode = ENGLISH_200;
    app->next_state = APP_NEW_TEST;
}

void init_app_ui(AppContext* app)
{
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    app->main_menu = menu_main_create(max_x);
    app->statistics = statistics_create();

    int ta_y = app->main_menu.panel->element_count + UI_BORDER_PADDING * 2;
    int stat_y = max_y / 3 + ta_y;

    app->testarea = test_area_create(max_x, ta_y, max_y);
    app->statistics_panel = statistics_panel_create(max_x, stat_y, &app->statistics);

    init_app_color_sceme(app);
}

void init_app_rendering(AppContext* app)
{
    app->ta_ctx = render_context_new(app->testarea.cont_win);
    ui_panel_curses_draw(&app->statistics_panel);
    ui_panel_curses_draw(&app->main_menu);
    ui_panel_curses_draw(&app->testarea);
}

void init_app(AppContext* app)
{
    init_curses();
    init_app_defaults(app);
    init_app_ui(app);
    init_app_rendering(app);
}

void destroy_app(AppContext* app)
{
    ui_panel_curses_destroy(&app->main_menu);
    ui_panel_curses_destroy(&app->testarea);
    ui_panel_curses_destroy(&app->statistics_panel);
    typing_test_destroy(&app->typing_test);
    endwin();
}
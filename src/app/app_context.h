#ifndef APP_STATE_H
#define APP_STATE_H

#include "domain/typing_test_mode.h"
#include "ui/colors.h"
#include "ui/ui_panel_curses.h"
#include "ui/render_context.h"
#include "domain/statistics.h"
#include "domain/typing_test.h"

typedef enum {
    APP_STARTUP,
    APP_NEW_TEST,
    APP_IN_TEST,
    APP_TEST_FINISHED,
    APP_STATISTICS,
    APP_QUIT,
    APP_TERMINATED
} AppState;

typedef struct {
    AppState state, next_state;
    UIPanelCurses main_menu, testarea, statistics_panel;
    TypingTestMode typing_test_mode;
    ColorScheme color_scheme;
    Statistics statistics;
    RenderContext ta_ctx;
    TypingTest typing_test;
} AppContext;

void init_app(AppContext* app);

void destroy_app(AppContext* app);

#endif
#include "menu_panel.h"

#include "backend/ui_panel.h"

#include "ui/ui_constants.h"
#include "ui/menu_item_draw_curses.h"
#include "ui/colors.h"

#include <stdlib.h>

#define TITLE_ROW 0
#define STATISTICS_ROW 1
#define MODE_ROW 2
#define RESTART_ROW 3
#define QUIT_ROW 4

void menu_item_cycle_color_scheme_action(AppContext* app)
{
    app->color_scheme += 1;
    app->color_scheme %= NBR_COLOR_SHEMES;
    app->next_state = APP_SET_COLOR;
}
void menu_item_restart_action(AppContext* app)
{
    app->next_state = APP_NEW_TEST;
}

void menu_item_quit_action(AppContext* app)
{
    app->next_state = APP_QUIT;
}

void menu_item_statistics_action(AppContext* app)
{
    // app->next_state = APP_STATISTICS;
    (void)* app;
}

void update_mode_menu_item(MenuItem* item, TypingTestMode mode)
{
    static char buffer[64];
    snprintf(buffer, sizeof(buffer),
             "mode: %s",
             typing_test_mode_names[mode]);
    item->text = buffer;
}

void menu_item_test_mode_select_action(AppContext* app)
{
    app->typing_test_mode =
        (TypingTestMode)(app->typing_test_mode + 1) % TYPING_TEST_MODE_COUNT;
    update_mode_menu_item(app->main_menu.panel->elements[MODE_ROW].impl,
                          app->typing_test_mode);
    app->next_state = APP_NEW_TEST;
}

UIElement ui_menu_item_create(MenuItem* item) {
    MenuItem* copy = malloc(sizeof(MenuItem));
    *copy = *item;
    UIElement el;
    el.impl = copy;
    el.draw = menu_item_draw_adapter;
    return el;
}

UIPanelCurses menu_main_create(int max_x)
{
    int element_count = 5;

    MenuItem title = {
        .row = TITLE_ROW,
        .text = "K-E-Y-S-M-A-S-H",
        .enabled = true,
        .action = menu_item_cycle_color_scheme_action};
    MenuItem statistics = {
        .row = STATISTICS_ROW,
        .text = "Statistics",
        .enabled = true,
        .action = menu_item_statistics_action};
    MenuItem mode = {
        .row = MODE_ROW,
        .text = "",
        .enabled = true,
        .action = menu_item_test_mode_select_action};
    MenuItem restart = {
        .row = RESTART_ROW,
        .text = "restart",
        .enabled = true,
        .action = menu_item_restart_action};
    MenuItem quit = {
        .row = QUIT_ROW,
        .text = "QUIT(esc)",
        .enabled = true,
        .action = menu_item_quit_action};

    UIElement* elements = malloc(sizeof(UIElement) * element_count);
    elements[TITLE_ROW] = ui_menu_item_create(&title);
    elements[STATISTICS_ROW] = ui_menu_item_create(&statistics);
    elements[MODE_ROW] = ui_menu_item_create(&mode);
    elements[RESTART_ROW] = ui_menu_item_create(&restart);
    elements[QUIT_ROW] = ui_menu_item_create(&quit);

    UIPanel *menu = (UIPanel *)malloc(sizeof(UIPanel));
    menu->element_count = element_count;
    menu->height = element_count + UI_BORDER_PADDING;
    menu->width = max_x-10;
    menu->x = 5;  // pass these as parameters maybe
    menu->y = 2;
    menu->selected = 3;
    menu->elements = elements;
    update_mode_menu_item(elements[MODE_ROW].impl, ENGLISH_200);

    return ui_panel_curses_create(menu);
}


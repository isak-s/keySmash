#include "menu_panel.h"

#include "backend/ui_panel.h"

#include "ui/ui_constants.h"
#include "ui/menu_item_draw_curses.h"

#include <stdlib.h>

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
    app->next_state = APP_STATISTICS;
}
// refactor!
void menu_item_test_mode_select_action(AppContext* app)
{
    app->typing_test_mode = ENGLISH_200;
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
        .row = 0,
        .text = "K-E-Y-S-M-A-S-H",
        .enabled = false,
        .action = menu_item_restart_action};
    MenuItem statistics = {
        .row = 1,
        .text = "Statistics",
        .enabled = true,
        .action = menu_item_statistics_action};
    MenuItem mode = {
        .row = 2,
        .text = "Mode: Quote english",
        .enabled = true,
        .action = menu_item_test_mode_select_action};
    MenuItem restart = {
        .row = 3,
        .text = "restart",
        .enabled = true,
        .action = menu_item_restart_action};
    MenuItem quit = {
        .row = 4,
        .text = "QUIT(esc)",
        .enabled = true,
        .action = menu_item_quit_action};

    UIElement* elements = malloc(sizeof(UIElement) * element_count);
    elements[0] = ui_menu_item_create(&title);
    elements[1] = ui_menu_item_create(&statistics);
    elements[2] = ui_menu_item_create(&mode);
    elements[3] = ui_menu_item_create(&restart);
    elements[4] = ui_menu_item_create(&quit);

    UIPanel *menu = (UIPanel *)malloc(sizeof(UIPanel));
    menu->element_count = element_count;
    menu->height = element_count + UI_BORDER_PADDING;
    menu->width = max_x-10;
    menu->x = 5;  // pass these as parameters maybe
    menu->y = 2;
    menu->selected = 3;
    menu->elements = elements;

    return ui_panel_curses_create(menu);
}


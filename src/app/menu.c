#include "menu.h"
#include "backend/ui_panel.h"
#include "backend/menu_adapter.h"
#include <stdlib.h>
#include "ui/ui_constants.h"

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

void handle_menu_input(UIPanelCurses* menu, MenuInput* inp, AppContext* app)
{
    switch (inp->type)
    {
    case M_ARROW_DOWN:
        menu->panel->selected++;
        menu->panel->selected %= menu->panel->element_count;
        break;
    case M_ARROW_UP:
        menu->panel->selected--;
        if (menu->panel->selected < 0) {
            menu->panel->selected = menu->panel->element_count - 1;
        }
        break;
    case M_ENTER:
        MenuItem* item = menu->panel->elements[menu->panel->selected].impl;
        if (item->enabled) item->action(app);
    default:
        break;
    }
}

UIPanelCurses statistics_panel_create(int max_x, int y, Statistics* stat)
{
    int element_count = 3;

    StatisticsItem word_count = { .row = 0, .text = "WPM: %d", .enabled = false, .stat = stat};
    StatisticsItem incorrect_count = { .row = 1, .text = "INCORRECT: %d", .enabled = false, .stat = stat};
    StatisticsItem curr_word = { .row = 2, .text = "-| %s |-", .enabled = false, .stat = stat};

    UIElement* elements = malloc(sizeof(UIElement) * element_count);
    elements[0] = ui_statistics_wpm_item_create(&word_count);
    elements[1] = ui_statistics_incorrect_item_create(&incorrect_count);
    elements[2] = ui_statistics_currword_item_create(&curr_word);
    UIPanel * stat_panel = malloc(sizeof(UIPanel));
    stat_panel->element_count = element_count;
    stat_panel->elements = elements;
    stat_panel->height = element_count + UI_BORDER_PADDING;
    stat_panel->width = max_x - 10;
    stat_panel->x = 5;
    stat_panel->y = y;

    return ui_panel_curses_create(stat_panel);
}
#include "menu.h"
#include "backend/ui_panel.h"
#include "backend/menu_adapter.h"
#include <stdlib.h>
#include "ui/ui_constants.h"

UIPanelCurses menu_main_create(int max_x)
{
    int element_count = 4;


    MenuItem item1 = { .row = 0, .text = "K_E_Y_S_M_A_S_H", .enabled = true };
    MenuItem item2 = { .row = 1, .text = "Statistics", .enabled = true };
    MenuItem item4 = { .row = 2, .text = "Mode: Quote english", .enabled = true };
    MenuItem item3 = { .row = 3, .text = "QUIT(esc)", .enabled = true };

    UIElement* elements = malloc(sizeof(UIElement) * element_count);
    elements[0] = ui_menu_item_create(&item1);
    elements[1] = ui_menu_item_create(&item4);
    elements[2] = ui_menu_item_create(&item2);
    elements[3] = ui_menu_item_create(&item3);

    UIPanel *menu = (UIPanel *)malloc(sizeof(UIPanel));
    menu->element_count = element_count;
    menu->height = element_count + UI_BORDER_PADDING;
    menu->width = max_x-10;
    menu->x = 5;  // pass these as parameters maybe
    menu->y = 2;
    menu->elements = elements;

    return ui_panel_curses_create(menu);
}

UIPanelCurses statistics_panel_create(int max_x, int y)
{
    int element_count = 2;

    MenuItem word_count = { .row = 0, .text = "WPM: 00", .enabled = false};
    MenuItem incorrect_count = { .row = 1, .text = "INCORRECT: 00", .enabled = false};

    UIElement* elements = malloc(sizeof(UIElement) * element_count);
    elements[0] = ui_menu_item_create(&word_count);
    elements[1] = ui_menu_item_create(&incorrect_count);
    UIPanel * stat = malloc(sizeof(UIPanel));
    stat->element_count = element_count;
    stat->elements = elements;
    stat->height = element_count + UI_BORDER_PADDING;
    stat->width = max_x - 10;
    stat->x = 5;
    stat->y = y;

    return ui_panel_curses_create(stat);
}
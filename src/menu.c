#include "menu.h"
#include "ui_panel.h"
#include "menu_adapter.h"
#include <stdlib.h>

UIPanelCurses menu_main_create(int max_x)
{
    int element_count = 4;


    MenuItem item1 = { .text = "Start typing", .enabled = true };
    MenuItem item2 = { .text = "Statistics", .enabled = true };
    MenuItem item4 = { .text = "Mode", .enabled = true };
    MenuItem item3 = { .text = "QUIT", .enabled = true };

    UIElement* elements = malloc(sizeof(UIElement) * element_count);
    elements[0] = ui_menu_item_create(&item1);
    elements[1] = ui_menu_item_create(&item2);
    elements[2] = ui_menu_item_create(&item4);
    elements[3] = ui_menu_item_create(&item3);

    UIPanel *menu = (UIPanel *)malloc(sizeof(UIPanel));
    menu->element_count = element_count;
    menu->height = element_count + 2; // for border
    menu->width = max_x-10;
    menu->x = 5;  // pass these as parameters maybe
    menu->y = 2;
    menu->elements = elements;


    return ui_panel_curses_create(menu);
}
#include "menu_adapter.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "ui/ui_panel_curses.h"


// new:
#include "ui/menu_item_draw_curses.h"
#include "ui/statistics_item_draw_curses.h"


UIElement ui_menu_item_create(MenuItem* item) {
    MenuItem* copy = malloc(sizeof(MenuItem));
    *copy = *item;
    UIElement el;
    el.impl = copy;
    el.draw = menu_item_draw_adapter;
    return el;
}

UIElement ui_statistics_wpm_item_create(StatisticsItem* item)
{
    StatisticsItem* copy = malloc(sizeof(StatisticsItem));
    *copy = *item;
    UIElement el;
    el.impl = copy;
    el.draw = statistics_menu_wpm_draw_adapter;
    return el;
}

UIElement ui_statistics_incorrect_item_create(StatisticsItem* item)
{
    StatisticsItem* copy = malloc(sizeof(StatisticsItem));
    *copy = *item;
    UIElement el;
    el.impl = copy;
    el.draw = statistics_menu_incorrect_draw_adapter;
    return el;
}

UIElement ui_statistics_currword_item_create(StatisticsItem* item)
{
    StatisticsItem* copy = malloc(sizeof(StatisticsItem));
    *copy = *item;
    UIElement el;
    el.impl = copy;
    el.draw = statistics_menu_curr_word_draw_adapter;
    return el;
}
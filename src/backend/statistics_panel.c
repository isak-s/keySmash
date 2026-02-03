#include "statistics_panel.h"
#include "ui/statistics_item_draw_curses.h"
#include "ui/ui_constants.h"

#include "stdlib.h"

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
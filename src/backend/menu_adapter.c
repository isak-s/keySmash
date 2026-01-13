#include "menu_adapter.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "ui/ui_panel_curses.h"

void menu_item_draw_adapter(UIElement* el, void* ctx) {
    UIPanelCurses* pc = ctx;
    MenuItem* item = el->impl;
    int pos = pc->panel->width / 2 - strlen(item->text) / 2 - 1; // 0 indexed!
    mvwprintw(pc->cont_win, item->row, pos, "%s", item->text);
}

UIElement ui_menu_item_create(MenuItem* item) {
    MenuItem* copy = malloc(sizeof(MenuItem));
    *copy = *item;
    UIElement el;
    el.impl = copy;
    el.draw = menu_item_draw_adapter;
    return el;
}

void statistics_menu_wpm_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    char str[32];
    snprintf(str, sizeof(str), item->text, item->stat->wpm);
    int pos = pc->panel->width / 2 - strlen(str);

    mvwprintw(pc->cont_win, item->row, pos, "%s", str);
}

void statistics_menu_incorrect_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    char str[32];
    snprintf(str, sizeof(str), item->text, item->stat->nbr_incorrect);
    int pos = pc->panel->width / 2 - strlen(str);

    mvwprintw(pc->cont_win, item->row, pos, "%s", str);
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
#include "statistics_item_draw_curses.h"

#include "ui_panel_curses.h"

// move stuff in this:
#include "app/menu.h"

void statistics_menu_wpm_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    char str[32];
    int len = snprintf(str, sizeof(str), item->text, item->stat->wpm);
    int pos = (pc->panel->width - len) / 2 - 1;
    mvwprintw(pc->cont_win, item->row, pos, "%s", str);
}

void statistics_menu_incorrect_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    char str[32];
    int len = snprintf(str, sizeof(str), item->text, item->stat->nbr_incorrect);
    int pos = (pc->panel->width - len) / 2 - 1;
    mvwprintw(pc->cont_win, item->row, pos, "%s", str);
}

void statistics_menu_curr_word_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    char str[32];
    int len = snprintf(str, sizeof(str), item->text, item->stat->currword);
    int pos = (pc->panel->width - len) / 2 - 1;
    mvwprintw(pc->cont_win, item->row, pos, "%s", str);
}

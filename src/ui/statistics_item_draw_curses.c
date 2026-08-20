#include "statistics_item_draw_curses.h"

#include "ui_panel_curses.h"
#include "backend/statistics_panel.h"

void statistics_menu_wpm_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    char str[32];
    int len = snprintf(str, sizeof(str), item->text, item->stat->wpm);
    int pos = (pc->panel->width - len) / 2 - 1;
    mvwprintw(pc->cont_win, item->row, pos, "%s", str);
}

void statistics_menu_accuracy_draw_adapter(UIElement* el, void* ctx)
{
    UIPanelCurses* pc = ctx;
    StatisticsItem* item = el->impl;
    // calculate accuracy
    int correct = item->stat->nbr_correct;
    int incorrect = item->stat->nbr_incorrect;
    float accuracy_percent = correct == 0
        ? 100
        : (((float) correct * 100) / (correct + incorrect));

    char str[32];
    int len = snprintf(str, sizeof(str), item->text, accuracy_percent);
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

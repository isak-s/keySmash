#include "menu_item_draw_curses.h"
#include "ui_panel_curses.h"

#include "string.h"
// move these files:
#include "app/menu.h"

void menu_item_draw_adapter(UIElement* el, void* ctx) {
    UIPanelCurses* pc = ctx;
    MenuItem* item = el->impl;
    int pos = (pc->panel->width - strlen(item->text)) / 2 - 1; // 0 indexed!

    bool selected = (pc->panel->selected == item->row);
    if (selected) wattron(pc->cont_win, A_UNDERLINE | A_BOLD);
    mvwprintw(pc->cont_win, item->row, pos, "%s", item->text);
    if (selected) wattroff(pc->cont_win, A_UNDERLINE | A_BOLD);
}

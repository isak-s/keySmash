#include "menu_adapter.h"
#include <ncurses.h>
#include <string.h>

void menu_item_draw_adapter(UIElement* el, void* ctx) {
    static int row = 1;  // TEMP: reset per frame later

    UIPanelCurses* pc = ctx;
    MenuItem* item = el->impl;
    int pos = pc->panel->width / 2 - strlen(item->text) / 2;
    mvwprintw(pc->win, row++, pos, "%s", item->text);
}

UIElement ui_menu_item_create(MenuItem* item) {
    UIElement el;
    el.impl = item;
    el.draw = menu_item_draw_adapter;
    return el;
}

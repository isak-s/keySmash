#include "menu_adapter.h"
#include <ncurses.h>

void menu_item_draw_adapter(UIElement* el, void* ctx) {
    static int row = 1;  // TEMP: reset per frame later

    UIPanelCurses* pc = ctx;
    MenuItem* item = el->impl;

    mvwprintw(pc->win, row++, 1, "%s", item->text);
}

UIElement ui_menu_item_create(MenuItem* item) {
    UIElement el;
    el.impl = item;
    el.draw = menu_item_draw_adapter;
    return el;
}

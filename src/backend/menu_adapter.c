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

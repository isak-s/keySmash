#ifndef MENU_H
#define MENU_H

#include "backend/ui_element.h"
#include <stddef.h>
#include <stdbool.h>
#include "ui/ui_panel_curses.h"

typedef struct {
    const char* text;
    bool enabled;
    int row;
} MenuItem;

// MenuItem* menu_item_create(const char* text);

UIPanelCurses menu_main_create(int max_x);

UIPanelCurses statistics_panel_create(int max_x, int y);

#endif

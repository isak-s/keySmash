#ifndef MENU_H
#define MENU_H

#include "ui_element.h"
#include <stddef.h>
#include <stdbool.h>
#include "ui_panel_curses.h"

typedef struct {
    const char* text;
    bool enabled;
} MenuItem;

// MenuItem* menu_item_create(const char* text);

UIPanelCurses menu_main_create(int max_x);

#endif

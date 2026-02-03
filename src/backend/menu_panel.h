#ifndef MENU_H
#define MENU_H

#include "backend/menu_input.h"

#include "ui/ui_panel_curses.h"

#include "app/app_context.h"

#include <stddef.h>
#include <stdbool.h>

typedef void (*MenuAction)(AppContext* app_state);

typedef struct {
    const char* text;
    bool enabled;
    int row;
    MenuAction action;
} MenuItem;

UIPanelCurses menu_main_create(int max_x);

#endif
